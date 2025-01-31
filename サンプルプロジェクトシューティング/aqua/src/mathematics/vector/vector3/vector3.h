
/*!
 *  @file       vector3.h
 *  @brief      3次元ベクトル
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include<DxLib.h>

namespace aqua
{
    using _Vector3 = DxLib::VECTOR;
    using _Matrix = DxLib::MATRIX;

    /*!
     *  @class      CVector3
     *
     *  @brief      3次元ベクトルクラス
     *
     *  @author     Kazuto Shimazaki
     *
     *  @date       2023/04/10
     *
     *  @version    7.17
     */
    class CVector3 : public VECTOR
	{
	public:
        /*!
         *  @brief  コンストラクタ
         */
        CVector3(void);

        /*!
         *  @brief  コンストラクタ
         *
         *  @param[in]  x   X成分
         *  @param[in]  y   Y成分
         */
        CVector3(float x, float y, float z);

        /*!
         *  @brief  コンストラクタ
         *
         *  @param[in]  v  ベクトル
         */
        CVector3(const _Vector3& v);

        /*!
         *  @brief  デストラクタ
         */
        ~CVector3(void) = default;


        /*!
         *  @brief      ベクトルの正規化<br>
         *              自身のベクトルも正規化される
         *
         *  @return     正規化されたベクトル
         */
        CVector3            Normalize(void);

        /*!
         *  @brief      ベクトルの正規化
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     正規化されたベクトル
         */
        static CVector3     Normalize(const _Vector3& v);

        /*!
         *  @brief      ベクトルの大きさ取得
         *
         *  @return     ベクトルの大きさ
         */
        float               Length(void);

        /*!
         *  @brief      ベクトルの大きさ取得
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルの大きさ
         */
        static float        Length(const _Vector3& v);

        /*!
         *  @brief      2つのベクトルの内積<br>
         *              dot = vA・vB
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     内積
         */
        static float        Dot(const _Vector3& vA, const _Vector3& vB);

        /*!
         *  @brief      2つのベクトルの外積<br>
         *              cross = vA×vB
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     外積
         */
        static CVector3        Cross(const _Vector3& vA, const _Vector3& vB);

        /*!
         *  @brief      代入演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        CVector3& operator=(const _Vector3& v)
        {
            x = v.x;
            y = v.y;
            z = v.z;

            return *this;
        }

        /*!
         *  @brief      加算演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        CVector3& operator+=(const _Vector3& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;

            return *this;
        }
        

        /*!
         *  @brief      減算演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        CVector3& operator-=(const _Vector3& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;

            return *this;
        }

        /*!
         *  @brief      乗算演算子のオーバーロード
         *
         *  @param[in]  scalar  スカラー値
         *
         *  @return     ベクトルクラス
         */
        CVector3& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;

            return *this;
        }

        /*!
         *  @brief      等価演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     二つのベクトルが等しい
         *  @retval     true    等しい
         *  @retval     false   等しくない
         */
        bool                operator==(const _Vector3& v) const { return (x == v.x && y == v.y && z == v.z); }

        /*!
         *  @brief      不等演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     二つのベクトルが等しくない
         *  @retval     true    等しくない
         *  @retval     false   等しい
         */
        bool                operator!=(const _Vector3& v) const { return (x != v.x || y != v.y && z != v.z); }

        /*!
         *  @brief      正符号演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator+(const _Vector3& v) { return v; }

        /*!
         *  @brief      負符号演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator-(const _Vector3& v) { return CVector3(-v.x, -v.y,-v.z); }

        /*!
         *  @brief      加算演算子のオーバーロード
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator+(const _Vector3& vA, const _Vector3& vB) { return aqua::CVector3(vA.x + vB.x, vA.y + vB.y, vA.z + vB.z); }

        /*!
         *  @brief      減算演算子のオーバーロード
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator-(const _Vector3& vA, const _Vector3& vB) { return CVector3(vA.x - vB.x, vA.y - vB.y, vA.z - vB.z); }

        /*!
         *  @brief      乗算演算子のオーバーロード
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator*(const _Vector3& vA, const _Vector3& vB) { return CVector3(vA.x * vB.x, vA.y * vB.y, vA.z * vB.z); }

        /*!
         *  @brief      乗算演算子のオーバーロード
         *
         *  @param[in]  v       ベクトルクラス
         *  @param[in]  scalar  スカラー値
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator*(const _Vector3& v, float scalar) { return CVector3(v.x * scalar, v.y * scalar, v.z * scalar); }

        /*!
         *  @brief      乗算演算子のオーバーロード
         *
         *  @param[in]  scalar  スカラー値
         *  @param[in]  v       ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator*(float scalar, const _Vector3& v) { return CVector3(v.x * scalar, v.y * scalar, v.z * scalar); }

        /*!
         *  @brief      除算演算子のオーバーロード
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator/(const _Vector3& vA, const _Vector3& vB) { return CVector3(vA.x / vB.x, vA.y / vB.y, vA.z / vB.z); }

        /*!
         *  @brief      除算演算子のオーバーロード
         *
         *  @param[in]  v       ベクトルクラス
         *  @param[in]  scalar  スカラー値
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator/(const _Vector3& v, float scalar) { return CVector3(v.x / scalar, v.y / scalar, v.z / scalar); }

        /*!
         *  @brief      除算演算子のオーバーロード
         *
         *  @param[in]  scalar  スカラー値
         *  @param[in]  v       ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator/(float scalar, const _Vector3& v) { return CVector3(scalar / v.x, scalar / v.y, scalar / v.z); }


        inline CVector3& operator*=(const _Matrix& mat)
        {
            (*this) = VTransform(*this, mat);

            return *this;
        }

        friend CVector3 operator*(const _Vector3& v, const _Matrix& mat) { return VTransform(v ,mat); }

        /*!
         *  @brief      デバッグログに値を表示する
         */
        void                DebugLog(void);


        // 成分がすべて0のベクトル
        static const CVector3   ZERO;
        // 成分がすべて1のベクトル
        static const CVector3   ONE;

        // 単方向のベクトル
        static const CVector3 FRONT;
        static const CVector3 BACK;
        static const CVector3 UP;
        static const CVector3 DOWN;
        static const CVector3 RIGHT;
        static const CVector3 LEFT;
	};
}