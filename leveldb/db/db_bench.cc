#include <cassert>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "leveldb/db.h"
#include "leveldb/write_batch.h"

const std::string kDBPath = "db_level";

void FillSeq(leveldb::DB* db, int num_entries, int value_size) {
    leveldb::WriteOptions write_options;
    std::string value(value_size, 'x');

    for (int i = 0; i < num_entries; ++i) {
        std::string key = "user" + std::to_string(i);
        db->Put(write_options, key, value);
    }
}

void ReadRandom(leveldb::DB* db, int num_entries, int value_size) {
    leveldb::ReadOptions read_options;
    std::string result;
    int found = 0;

    for (int i = 0; i < num_entries; ++i) {
        int rand_key = rand() % num_entries;
        std::string key = "user" + std::to_string(rand_key);
        leveldb::Status s = db->Get(read_options, key, &result);
        if (s.ok()) ++found;
    }

    std::cout << "Found " << found << " of " << num_entries << " keys." << std::endl;
}

template <typename F>
void Benchmark(const std::string& name, F func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto finish = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
    double micros_per_op = static_cast<double>(duration.count()) / 100000;

    std::cout << name << " : " << micros_per_op << " micros/op, "
              << 1000000.0 / micros_per_op << " ops/sec" << std::endl;
}

int main(int argc, char** argv) {
    const int num_entries = 100000;
    const int value_size = 400;

    std::string mode = argc > 1 ? argv[1] : "fillseq";

    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, kDBPath, &db);
    assert(status.ok());

    if (mode == "fillseq") {
        Benchmark("fillseq", [&]() {
            FillSeq(db, num_entries, value_size);
        });
    } else if (mode == "readrandom") {
        Benchmark("readrandom", [&]() {
            ReadRandom(db, num_entries, value_size);
        });
    } else if (mode == "readseq") {
    	Benchmark("readseq", [&]() {
        	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
        	for (it->SeekToFirst(); it->Valid(); it->Next()) {
            	// Optionally: std::string key = it->key().ToString();
        	}
        	assert(it->status().ok());
        	delete it;
    	});
    } else if (mode == "deleterandom") {
    	Benchmark("deleterandom", [&]() {
        	leveldb::WriteOptions write_options;
        	for (int i = 0; i < num_entries; ++i) {
            		int rand_key = rand() % num_entries;
            		std::string key = "user" + std::to_string(rand_key);
            		db->Delete(write_options, key);
        	}
    	});
    } else if (mode == "readwhilewriting") {
    	Benchmark("readwhilewriting", [&]() {
        	leveldb::WriteOptions write_options;
        	leveldb::ReadOptions read_options;
        	std::string result;

        	for (int i = 0; i < num_entries; ++i) {
            		// 쓰기
            		std::string key = "user" + std::to_string(i + num_entries);
            		std::string value(400, 'x');
            		db->Put(write_options, key, value);

            		// 읽기
            		int rand_key = rand() % num_entries;
            		std::string read_key = "user" + std::to_string(rand_key);
            		db->Get(read_options, read_key, &result);
        	}
    	});
    } else {
        std::cerr << "Unknown benchmark: " << mode << std::endl;
    }

    delete db;
    return 0;
}
