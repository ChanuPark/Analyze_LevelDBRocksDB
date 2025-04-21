#!/bin/bash
echo "▶ RocksDB readrandom 시작"

./rocksdb/db_bench \
  --benchmarks=readrandom \
  --num=100000 \
  --value_size=400 \
  --compression_type=snappy \
  --db=db_rocks \
  --use_existing_db=true \
  > results/readrandom_rocksdb.txt

echo "✅ 완료! 결과는 results/readrandom_rocksdb.txt"

