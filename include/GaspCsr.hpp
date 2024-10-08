#ifndef GASP_CSR_HPP
#define GASP_CSR_HPP

#include "common.h"
#include "utils.cuh"


namespace gasp {

/* Data type, index type */
template <typename D, typename I>
class GaspCsr
{

public:

    GaspCsr(size_t _m, size_t _n, size_t _nnz,
            D * _d_vals, I * _d_colinds, 
            I * _d_rowptrs):
        m(_m), n(_n), nnz(_nnz),
        d_vals(_d_vals), d_colinds(_d_colinds),
        d_rowptrs(_d_rowptrs)
        {}

    void dump(std::ofstream& ofs)
    {
        ofs<<"VALS:"<<std::endl;
        utils::write_device_buffer(nnz, d_vals, ofs);
        ofs<<"COLINDS:"<<std::endl;
        utils::write_device_buffer(nnz, d_colinds, ofs);
        ofs<<"ROWPTRS:"<<std::endl;
        utils::write_device_buffer(m+1, d_rowptrs, ofs);
    }

    ~GaspCsr()
    {
        CUDA_FREE_SAFE(d_vals);
        CUDA_FREE_SAFE(d_colinds);
        CUDA_FREE_SAFE(d_rowptrs);
    }

    inline size_t get_rows() const { return m; }
    inline size_t get_cols() const { return n; }
    inline size_t get_nnz() const { return nnz; }

    inline size_t get_val_bytes() const { return sizeof(D); }
    inline size_t get_ind_bytes() const { return sizeof(I); }
    inline size_t get_tuple_bytes() const { return sizeof(I)*2 + sizeof(D); }

    inline D * get_vals() const { return d_vals; }
    inline I * get_colinds() const { return d_colinds; }
    inline I * get_rowptrs() const { return d_rowptrs; }

private:

    size_t m, n, nnz;
    D * d_vals;
    I * d_colinds, * d_rowptrs;

};

}


#endif
