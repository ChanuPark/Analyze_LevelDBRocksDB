#!/bin/bash
echo "▶ RocksDB readseq 시작"

./rocksdb/db_bench --benchmarks=readseq \
  --num=100000 \
  --value_size=400 \
  --use_existing_db=true \
  --db=db_rocks \
  > results/readseq_rocksdb.txt

echo "✅ 완료! 결과는 results/readseq_rocksdb.txt"
