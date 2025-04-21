#!/bin/bash
echo "▶ RocksDB deleterandom 시작"

./rocksdb/db_bench --benchmarks=deleterandom \
  --num=100000 \
  --value_size=400 \
  --use_existing_db=true \
  --db=db_rocks \
  > results/deleterandom_rocksdb.txt

echo "✅ 완료! 결과는 results/deleterandom_rocksdb.txt"
