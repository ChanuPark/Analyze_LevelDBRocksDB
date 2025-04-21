#!/bin/bash
echo "▶ LevelDB fillseq 시작"

./leveldb/build/db_bench \
  --benchmarks=fillseq \
  --num=100000 \
  --value_size=400 \
  --use_existing_db=false \
  --db=db_level \
  > results/fillseq_leveldb.txt

echo "✅ 완료! 결과는 results/fillseq_leveldb.txt"
