#!/bin/bash
echo "▶ RocksDB readwhilewriting 시작"

./rocksdb/db_bench --benchmarks=readwhilewriting \
  --num=100000 \
  --value_size=400 \
  --use_existing_db=true \
  --db=db_rocks \
  > results/readwhilewriting_rocksdb.txt

echo "✅ 완료! 결과는 results/readwhilewriting_rocksdb.txt"

