#!/bin/bash
echo "▶ LevelDB readrandom 시작"

./leveldb/build/db_bench \
  --benchmarks=readrandom \
  --num=100000 \
  --value_size=400 \
  --use_existing_db=true \
  --db=db_level \
  > results/readrandom_leveldb.txt

echo "✅ 완료! 결과는 results/readrandom_leveldb.txt"
