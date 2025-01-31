/*!
 *  @file       life_bar.h
 *  @brief
 *  @brief
 *  @author     Kazuto Shimazaki
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "../ui_component.h"

 /*!
  *  @class      CLifeBar
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/06/05
  *
  *  @version    1.0
  */
class CLockOnMarker
    : public IUIComponent
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親のオブジェクト
     */
    CLockOnMarker(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CLockOnMarker(void) = default;

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

    /*!
     *  @brief      更新
     */
    void        Update(void)override;

    /*!
     *  @brief      描画
     */
    void        Draw(void) override;

    /*!
     *  @brief      解放
     */
    void        Finalize(void) override;

    void        SetTarget(IUnit* target) { m_Target = target; }

private:

    aqua::CSprite  m_Sprite;   // ロックオン画像スプライト

    aqua::CCamera* m_Camera;   // カメラのポインタ容器

    IUnit*         m_User;     // ロックオン使用者

    IUnit*         m_Target;   // ロックオン対象

    CGameMain*     m_GameMain; // ゲームメインシーンのポインタ容器
};
