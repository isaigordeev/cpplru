# cpplru

## step 1

create C extern run time

## step 2

proper cpp style for the pb - replica

## step 3

better hash table

## step 4

thread safety

## step 5

lock-free concurency
custom memory pools or arena allocators

## step 6

super tiny db project + check how mispredictions affects the db

## step 7

rl integration

##    

# Page & Record Layout

- Choose a fixed page size (e.g. 4 KB or 8 KB).
- Each page begins with a small header:
    - `page_id` (64 bit)
    - `lsn` (log sequence number, 64 bit)
    - `free_space_offset` (16 bit)
    - `slot_count` (16 bit)
- Use a slotted-page design: after the header you have an array of slots (each slot is a 16-bit offset into the page).
  Records are stored from the end of the page backward.
- **Record format**:
    - `record_length` (16 bit)
    - “tombstone” flag (for deletes)
    - `payload` (your columns or blob)

---  

# Page I/O Layer

- Expose two calls:
    - `read_page(page_id) → raw bytes`
    - `write_page(page_id, raw bytes)`
- Underneath use either:
    - `std::fstream` with `pread()`/`pwrite()` (POSIX), or
    - memory-mapped file (`mmap` with `MAP_SYNC` / DAX on PMEM), or
    - `O_DIRECT` + libaio/IO-uring for async I/O

---  

# Buffer-Pool Manager

- Maintain a fixed array of frames in DRAM; each frame holds one page’s bytes plus metadata:
    - `page_id`, `pin_count`, `dirty_bit`, `lsn`, `last_access_timestamp`
- A hashmap `page_id → frame_index` for lookup.
- **API:**
    - `pin_page(page_id)`: if in pool, `pin_count++`; else evict an unpinned frame (LRU/CLOCK/K), load from disk,
      `pin_count=1`.
    - `unpin_page(page_id, is_dirty)`: decrement `pin_count`; if `is_dirty` set `dirty_bit`.
    - `flush_page(page_id)`: if dirty write back.
- **Eviction**: scan for `pin_count == 0`, pick the “coldest” or use CLOCK.

---  

# Write-Ahead Log (WAL)

- Every modification generates a log record:
    - `{txn_id, page_id, slot, old_bytes, new_bytes, prev_lsn}`
- Append to an append-only log file; assign each record an LSN.
- On commit: issue `fsync()` on the log file up to the highest LSN for that txn (group-commit is OK).
- Only after log is on disk may you allow dirty pages to be flushed.

---  

# Crash Recovery

- On startup read the log from the last checkpoint LSN:
    - REDO all log records ≥ `checkpoint_lsn` (apply `new_bytes`).
    - UNDO any uncommitted txn’s changes (using `old_bytes`).

---  

# MVCC / Concurrency (optional)

- Instead of in-place updates you can append new versions:
    - Each record header carries a `begin_lsn` and `end_lsn`.
- Readers pick the version whose `begin_lsn ≤ snapshot_lsn < end_lsn`.
- Garbage-collect old versions once no active snapshot needs them.

---  

# Modern Enhancements

a) **Memory-mapped pages on Persistent Memory (PMEM)**

- Use `libpmemobj` or `mmap + MAP_SYNC` to bypass OS cache, flush via `CLWB + SFENCE`.

b) **Log-Structured Merge trees (LSM) for write-heavy workloads**

- Batch inserts in an in-memory memtable, flush SSTables on disk, compact in background.
- Use bloom filters per file to speed up point lookups.

c) **Page compression**

- At eviction time compress with LZ4 or Zstd; on load decompress.

d) **Vectorized scans**

- Store columns separately in pages (column-store) and use SIMD for batch filtering.

e) **Hardware-accelerated crypto/compression**

- Utilize Intel ISA-L or ARM Crypto extensions for acceleration.

---  

# Step-by-step Implementation Sketch

1. Create a **Page** class
    - Holds `byte[PAGE_SIZE]`
    - Header accessors
    - Slot directory functions

2. Build **DiskManager**
    - `open()`, `read_page()`, `write_page()`

3. Build **BufferPoolManager**
    - Vector of frames
    - `unordered_map<page_id, frame_idx>` page table
    - `fix_page()`, `unfix_page()`
    - Eviction policy implementation

4. Build **LogManager**
    - `append(log_record)`
    - `flush(lsn)`

5. Expose a simple **StorageEngine API**
    - `begin_txn()`, `commit_txn()`, `abort_txn()`
    - `insert(page_id, record)`, `update(page_id, slot, new_payload)`, `delete(page_id, slot)`

6. Wire operations
    - On insert/update/delete:
        - Produce a log record
        - Call LogManager
        - Pin page in BufferPoolManager
        - Modify in memory
        - Unpin page (with `dirty=true`)

7. On startup
    - Call RecoveryManager to scan log and rebuild/restore indexes.

8. Add a background thread to flush dirty pages periodically or when log is fsynced.

9. (Optional) Add a simple B-Tree over pages for indexing
    - Use latch coupling and MVCC.

---  

# Iteration and Extensions

- Swap in an LSM-tree instead of a B-Tree.
- Replace LRU eviction with LFU-K.
- Plug in Persistent Memory (PMEM).
- Add columnar storage segments.
- Implement vectorized query execution.

---  

This basic architecture underpins most modern embedded databases such as SQLite, RocksDB, and WiredTiger.  
