/*
 * This file is part of EIBA.
 *
 * Copyright (C) 2017 Zhejiang University
 * For more information see <https://github.com/ZJUCVG/EIBA>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "PlatformIndependence/sse.h"

#ifndef _MATRIX_3x4_H_
#define _MATRIX_3x4_H_

#include "Matrix3x3.h"

namespace LA
{
class AlignedMatrix3x4f
{
  public:
    inline const _pi__m128 &m_00_01_02_03() const { return m_data[0]; }
    inline _pi__m128 &m_00_01_02_03() { return m_data[0]; }
    inline const _pi__m128 &m_10_11_12_13() const { return m_data[1]; }
    inline _pi__m128 &m_10_11_12_13() { return m_data[1]; }
    inline const _pi__m128 &m_20_21_22_23() const { return m_data[2]; }
    inline _pi__m128 &m_20_21_22_23() { return m_data[2]; }
    inline const float &m00() const { return m_data[0].m128_f32[0]; }
    inline float &m00() { return m_data[0].m128_f32[0]; }
    inline const float &m01() const { return m_data[0].m128_f32[1]; }
    inline float &m01() { return m_data[0].m128_f32[1]; }
    inline const float &m02() const { return m_data[0].m128_f32[2]; }
    inline float &m02() { return m_data[0].m128_f32[2]; }
    inline const float &m03() const { return m_data[0].m128_f32[3]; }
    inline float &m03() { return m_data[0].m128_f32[3]; }
    inline const float &m10() const { return m_data[1].m128_f32[0]; }
    inline float &m10() { return m_data[1].m128_f32[0]; }
    inline const float &m11() const { return m_data[1].m128_f32[1]; }
    inline float &m11() { return m_data[1].m128_f32[1]; }
    inline const float &m12() const { return m_data[1].m128_f32[2]; }
    inline float &m12() { return m_data[1].m128_f32[2]; }
    inline const float &m13() const { return m_data[1].m128_f32[3]; }
    inline float &m13() { return m_data[1].m128_f32[3]; }
    inline const float &m20() const { return m_data[2].m128_f32[0]; }
    inline float &m20() { return m_data[2].m128_f32[0]; }
    inline const float &m21() const { return m_data[2].m128_f32[1]; }
    inline float &m21() { return m_data[2].m128_f32[1]; }
    inline const float &m22() const { return m_data[2].m128_f32[2]; }
    inline float &m22() { return m_data[2].m128_f32[2]; }
    inline const float &m23() const { return m_data[2].m128_f32[3]; }
    inline float &m23() { return m_data[2].m128_f32[3]; }
    inline operator const float *() const { return (const float *)this; }
    inline operator float *() { return (float *)this; }
    inline void operator+=(const AlignedMatrix3x4f &M)
    {
        m_data[0] = _pi_mm_add_ps(M.m_data[0], m_data[0]);
        m_data[1] = _pi_mm_add_ps(M.m_data[1], m_data[1]);
        m_data[2] = _pi_mm_add_ps(M.m_data[2], m_data[2]);
    }
    inline void operator-=(const AlignedMatrix3x4f &M)
    {
        m_data[0] = _pi_mm_sub_ps(m_data[0], M.m_data[0]);
        m_data[1] = _pi_mm_sub_ps(m_data[1], M.m_data[1]);
        m_data[2] = _pi_mm_sub_ps(m_data[2], M.m_data[2]);
    }
    inline void operator*=(const _pi__m128 &s)
    {
        m_data[0] = _pi_mm_mul_ps(s, m_data[0]);
        m_data[1] = _pi_mm_mul_ps(s, m_data[1]);
        m_data[2] = _pi_mm_mul_ps(s, m_data[2]);
    }

    inline void Set(const float *M)
    {
        memcpy(&m00(), M, sizeof(AlignedMatrix3x4f));
    }
    inline void Set(const AlignedMatrix3x3f &M0, const AlignedVector3f &M1)
    {
        memcpy(&m00(), &M0.m00(), 12);
        m03() = M1.v0();
        memcpy(&m10(), &M0.m10(), 12);
        m13() = M1.v1();
        memcpy(&m20(), &M0.m20(), 12);
        m23() = M1.v2();
    }
    inline void Get(float *M) const
    {
        memcpy(M, &m00(), sizeof(AlignedMatrix3x4f));
    }

    inline void MakeZero() { memset(this, 0, sizeof(AlignedMatrix3x4f)); }
    inline void Print(const bool e = false) const
    {
        if (e) {
            UT::Print("%e %e %e %e\n", m00(), m01(), m02(), m03());
            UT::Print("%e %e %e %e\n", m10(), m11(), m12(), m13());
            UT::Print("%e %e %e %e\n", m20(), m21(), m22(), m23());
        } else {
            UT::Print("%f %f %f %f\n", m00(), m01(), m02(), m03());
            UT::Print("%f %f %f %f\n", m10(), m11(), m12(), m13());
            UT::Print("%f %f %f %f\n", m20(), m21(), m23(), m23());
        }
    }
    inline void AssertZero() const
    {
        UT::AssertEqual(
            SSE::Sum012(_pi_mm_mul_ps(m_00_01_02_03(), m_00_01_02_03())), 0.0f);
        UT::AssertEqual(
            SSE::Sum012(_pi_mm_mul_ps(m_10_11_12_13(), m_10_11_12_13())), 0.0f);
        UT::AssertEqual(
            SSE::Sum012(_pi_mm_mul_ps(m_20_21_22_23(), m_20_21_22_23())), 0.0f);
    }
    inline bool AssertEqual(const AlignedMatrix3x4f &M,
                            const int verbose = 1) const
    {
        if (UT::VectorAssertEqual(&m00(), &M.m00(), 12, 0)) return true;
        if (verbose) {
            UT::PrintSeparator();
            Print(verbose > 1);
            UT::PrintSeparator();
            M.Print(verbose > 1);
        }
        return false;
    }

    static inline void ATBToSymmetric(const AlignedMatrix3x3f &A,
                                      const AlignedMatrix3x4f &B,
                                      AlignedMatrix3x4f &ATB)
    {
        ATB.m_00_01_02_03() = _pi_mm_add_ps(
            _pi_mm_add_ps(
                _pi_mm_mul_ps(_pi_mm_set1_ps(A.m00()), B.m_00_01_02_03()),
                _pi_mm_mul_ps(_pi_mm_set1_ps(A.m10()), B.m_10_11_12_13())),
            _pi_mm_mul_ps(_pi_mm_set1_ps(A.m20()), B.m_20_21_22_23()));
        ATB.m_10_11_12_13() = _pi_mm_add_ps(
            _pi_mm_add_ps(
                _pi_mm_mul_ps(_pi_mm_set1_ps(A.m01()), B.m_00_01_02_03()),
                _pi_mm_mul_ps(_pi_mm_set1_ps(A.m11()), B.m_10_11_12_13())),
            _pi_mm_mul_ps(_pi_mm_set1_ps(A.m21()), B.m_20_21_22_23()));
        ATB.m22() = A.m02() * B.m02() + A.m12() * B.m12() + A.m22() * B.m22();
        ATB.m23() = A.m02() * B.m03() + A.m12() * B.m13() + A.m22() * B.m23();
    }

  protected:
    _pi__m128 m_data[3];
};
}

#ifdef CFG_DEBUG_EIGEN
class EigenMatrix3x4f : public Eigen::Matrix<float, 3, 4>
{
  public:
    inline EigenMatrix3x4f() = default;
    inline EigenMatrix3x4f(const Eigen::Matrix<float, 3, 4> &e_M)
        : Eigen::Matrix<float, 3, 4>(e_M)
    {
    }
    inline EigenMatrix3x4f(const LA::AlignedMatrix3x4f &M)
        : Eigen::Matrix<float, 3, 4>()
    {
        Eigen::Matrix<float, 3, 4> &e_M = *this;
        e_M(0, 0) = M.m00();
        e_M(0, 1) = M.m01();
        e_M(0, 2) = M.m02();
        e_M(0, 3) = M.m03();
        e_M(1, 0) = M.m10();
        e_M(1, 1) = M.m11();
        e_M(0, 2) = M.m02();
        e_M(0, 3) = M.m03();
        e_M(2, 0) = M.m20();
        e_M(2, 1) = M.m21();
        e_M(2, 2) = M.m22();
        e_M(2, 3) = M.m23();
    }
    inline EigenMatrix3x4f(const EigenMatrix3x3f &e_M0,
                           const EigenVector3f &e_M1)
    {
        block<3, 3>(0, 0) = e_M0;
        block<3, 1>(0, 3) = e_M1;
    }
    inline void operator=(const Eigen::Matrix<float, 3, 4> &e_M)
    {
        *((Eigen::Matrix<float, 3, 4> *)this) = e_M;
    }
    inline LA::AlignedMatrix3x4f GetAlignedMatrix3x4f() const
    {
        LA::AlignedMatrix3x4f M;
        const Eigen::Matrix<float, 3, 4> &e_M = *this;
        M.m00() = e_M(0, 0);
        M.m01() = e_M(0, 1);
        M.m02() = e_M(0, 2);
        M.m03() = e_M(0, 3);
        M.m10() = e_M(1, 0);
        M.m11() = e_M(1, 1);
        M.m12() = e_M(1, 2);
        M.m13() = e_M(1, 3);
        M.m20() = e_M(2, 0);
        M.m21() = e_M(2, 1);
        M.m22() = e_M(2, 2);
        M.m23() = e_M(2, 3);
        return M;
    }
    inline void Print(const bool e = false) const
    {
        GetAlignedMatrix3x4f().Print(e);
    }
    inline bool AssertEqual(const LA::AlignedMatrix3x4f &M,
                            const int verbose = 1) const
    {
        return GetAlignedMatrix3x4f().AssertEqual(M, verbose);
    }
    inline bool AssertEqual(const EigenMatrix3x4f &e_M,
                            const int verbose = 1) const
    {
        return AssertEqual(e_M.GetAlignedMatrix3x4f(), verbose);
    }
};
#endif
#endif
