# Analyze_LevelDBRocksDB

이 프로젝트는 LevelDB와 RocksDB의 성능을 다양한 벤치마크 테스트를 통해 비교하기 위한 실험용 저장소이다.  
추후 다양한 설정 변화에 따른 성능 비교, compaction 전략 실험, 압축 설정 테스트 등을 추가로 진행할 예정이다.

---

## 📁 디렉토리 구조

- `benchmark/` : 벤치마크 실행을 위한 `.sh` 스크립트 모음
- `results/` : 실험 결과 출력 파일 저장 경로
- `leveldb/` : 구글 LevelDB 공식 레포지토리 클론
- `rocksdb/` : 메타(Facebook) RocksDB 공식 레포지토리 클론
- `.gitignore` : 불필요한 빌드 파일, 로그, 결과파일을 Git 추적에서 제외

---

## 💻 실험 환경

- 운영체제: Ubuntu 22.04 LTS  
- 하이퍼바이저: KVM  
- CPU: 2 vCPU (1.00GHz x 2)  
- 메모리: 4GB  
- 내부 IP: 10.0.10.142  
- 컴파일러: gcc 11.4.0  
- CMake: 3.22 이상  
- LevelDB 버전: 1.23  
- RocksDB 버전: 10.1.3  

---

## ⚙️ 실행 방법

### 1. RocksDB 빌드

cd rocksdb
make db_bench -j4

### 2. LevelDB 빌드

cd leveldb
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DLEVELDB_BUILD_TESTS=OFF -DLEVELDB_BUILD_BENCHMARKS=OFF ..
cmake --build .

### 3. 벤치마크 실행

RocksDB(스크립트 실행)
bash benchmark/run_fillseq_rocksdb.sh
bash benchmark/run_readrandom_rocksdb.sh
bash benchmark/run_readseq_rocksdb.sh
bash benchmark/run_deleterandom_rocksdb.sh
bash benchmark/run_readwhilewriting_rocksdb.sh

LevelDB(직접 실행)
./leveldb/build/db_bench fillseq
./leveldb/build/db_bench readrandom
./leveldb/build/db_bench readseq
./leveldb/build/db_bench deleterandom
./leveldb/build/db_bench readwhilewriting

→ 각 실험 결과는 results/ 디렉토리에 자동 저장된다 (RocksDB의 경우)
→ LevelDB의 경우는 화면에 출력되므로, 필요한 경우 별도로 리다이렉션하여 저장할 수 있다.

---

📌 향후 계획
	•	압축 유형 변경 (snappy, none 등)에 따른 성능 분석
	•	compaction 전략별 차이 실험
	•	write amplification, space amplification 측정 실험
