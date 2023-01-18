// Copyright (C) 2022 Adam Lugowski. All rights reserved.
// Use of this source code is governed by the BSD 2-clause license found in the LICENSE.txt file.

#pragma once

#include <benchmark/benchmark.h>

#include <array>
#include <vector>

#include <fast_matrix_market/fast_matrix_market.hpp>

template <typename IT, typename VT>
struct triplet_matrix {
    int64_t nrows = 0, ncols = 0;
    std::vector<IT> rows;
    std::vector<IT> cols;
    std::vector<VT> vals;
};

template <typename VT>
struct array_matrix {
    int64_t nrows = 0, ncols = 0;
    std::vector<VT> vals;
};

/**
 * Construct a test matrix.
 * @param byte_target How big the matrix tuples should be
 */
template <typename IT, typename VT>
triplet_matrix<IT, VT> construct_triplet(std::size_t byte_target) {
    int64_t num_elements = byte_target / (2*sizeof(IT) + sizeof(VT));

    triplet_matrix<IT, VT> ret;

    ret.nrows = num_elements;
    ret.ncols = num_elements;

    ret.rows.reserve(num_elements);
    ret.cols.reserve(num_elements);
    ret.vals.reserve(num_elements);

    for (auto i = 0; i < num_elements; ++i) {
        ret.rows.emplace_back(i);
        ret.cols.emplace_back(i);
        ret.vals.emplace_back(static_cast<VT>(i) / 100);
    }

    return ret;
}

/**
 * Construct a test matrix.
 * @param byte_target How big the matrix tuples should be
 */
template <typename VT>
array_matrix<VT> construct_array(std::size_t byte_target) {
    int64_t num_elements = byte_target / (sizeof(VT));
    auto n = (int64_t)std::sqrt(num_elements);

    array_matrix<VT> ret;

    ret.nrows = n;
    ret.ncols = n;
    ret.vals.reserve(n*n);

    for (auto i = 0; i < n*n; ++i) {
        ret.vals.emplace_back(static_cast<VT>(i) / 100);
    }
    return ret;
}

/**
 * Constructs a large string block composed of repeated lines from kLines.
 *
 * @param byte_target size in bytes of the result
 */
std::string construct_large_coord_string(std::size_t byte_target);

constexpr int64_t kArrayTargetReadBytes = 256 * 2 << 20;
constexpr int64_t kArrayTargetWriteBytes = 256 * 2 << 20;
constexpr int64_t kCoordTargetReadBytes = 512 * 2 << 20;
constexpr int64_t kCoordTargetWriteBytes = 512 * 2 << 20;

/**
 * Set thread count benchmark arguments.
 */
void NumThreadsArgument(benchmark::internal::Benchmark* b);
