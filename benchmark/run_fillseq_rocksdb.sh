#!/bin/bash
echo "▶ RocksDB fillseq 시작"

./rocksdb/db_bench \
  --benchmarks=fillseq \
  --num=100000 \
  --value_size=400 \
  --compression_type=snappy \
  --db=db_rocks \
  --use_existing_db=false \
  > results/fillseq_rocksdb.txt

echo "✅ 완료! 결과는 results/fillseq_rocksdb.txt"
