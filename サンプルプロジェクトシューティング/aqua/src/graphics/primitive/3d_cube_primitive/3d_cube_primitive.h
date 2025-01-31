
/*!
 *  @file       line_primitive_3d.h
 *  @brief      3Düª`æNX
 *  @author     Toshihito Ohashi
 *  @date       2022/03/29
 *  @version    7.17
 *
 *  Copyright (c) 2021-2022, Toshihito Ohahsi. All rights reserved.
 */

#pragma once

#include <DxLib.h>
#include "..\..\alphablend\alphablend.h"
#include "..\..\draw_object\draw_object.h"
#include "..\..\..\mathematics\mathematics.h"
#include "..\..\color\color.h"
#include "..\..\..\utility\utility.h"

 /*!
  *  @brief      aqua¼OóÔ
  */
namespace aqua
{
    /*!
     *  @class      CCubePrimitive3D
     *
     *  @brief      üª`æNX
     *
     *  @author     Kazuto Shimazaki
     *
     *  @date       2023/04/14
     *
     *  @version    7.17
     */
    class CCubePrimitive
        : public aqua::core::IDrawObject, public CCollision
    {
    public:
        //! SÀW
        aqua::CVector3      position;
        //! ÚGÀW
        aqua::CVector3      collision_pos;
        //! 
        float               width;
        //! ³
        float               height;
        //! s
        float               depth;
        //! ¼ñ]px
        float           m_VRotate;
        //! ½ñ]px
        float           m_HRotate;
        //! Pèñ]px
        float           m_TRotate;

        //! F
        aqua::CColor        color;
        //! ½ËõF
        aqua::CColor        spc_color;
        //! hè×µ
        bool                fill;
        //! ¸_ÀWîñ
        tagVERTEX3D         vertex[8];

        // ÚGµ½ü«
        enum class COLL_DIRE
        {
            FRONT,
            RIGHT,
            BACK,
            LEFT,
            DOWN,
            UP
        };

        /*!
         *  @brief      RXgN^
         */
        CCubePrimitive(void);

        /*!
         *  @brief      fXgN^
         */
        ~CCubePrimitive(void) = default;
       
        /*!
         *  @brief      ú»
         *
         *  @param[in]  center_pos      SÀW
         *  @param[in]  width_          
         *  @param[in]  height_         ³
         *  @param[in]  depth           s
         *  @param[in]  color_          F
         *  @param[in]  spc_color_      ½ËõF
         *  @param[in]  fill_           hè×µ
         */
        void    Setup(const aqua::CVector3& center_pos, float width_, float height_, float depth, const aqua::CColor& color_ = 0xffffffff, const aqua::CColor& spc_color_ = 0xffffffff, bool fill_ = true);

        /*!
         *  @brief      Ï`
         */
        void    Transform(void);

        /*!
         *  @brief      `æ
         */
        void    Draw(void);

        /*!
         *  @brief      üªÕË»è
         *  @param[in]  pointA          n_
         *  @param[in]  pointB          I_
         */
        bool    CheckCollision(CVector3& pointA, CVector3& pointB)override;

        /*!
         *  @brief      ÕË»è
         *  @param[in]  center_pos      ÌS
         *  @param[in]  r               ¼a
         */
        bool    CheckCollision(CVector3& center_pos, float r)override;

        /*!
         *  @brief      ÕË»è
         *  @param[in]  center_pos      ÌS
         *  @param[in]  r               ¼a
         */
        bool    CheckCollision(CVector3& positionA, CVector3& positionB, float r)override;

        COLL_DIRE           GetLastCollDire(void) { return last_dire; }

    private:
        WORD                index[36];
        static const int    polygon_count;
        static const int    vertex_count;
        static const int    index_count;
        COLL_DIRE           last_dire;

    };
}
