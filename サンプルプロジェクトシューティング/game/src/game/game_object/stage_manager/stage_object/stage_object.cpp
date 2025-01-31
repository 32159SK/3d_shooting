/*
 *  @file       stage_object.cpp
 *  @brief      ステージオブジェクト
 *  @author
 *  @date
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#include "../../game_object.h"
#include "stage_object.h"

const float IStageObject::m_default_size = 25.0f;
const float IStageObject::m_transition_time = 3.0f;

/*
 *  コンストラクタ
 */
IStageObject::
IStageObject(aqua::IGameObject* parent, const std::string& name)
    : IGameObject(parent, name)
    , m_StageObjectID(NORMAL_BLOCK)
    , m_ObjectState(OBJECT_STATE::GO_IN)
    , m_ActiveFlag(true)
    , m_CollisionFlag(false)
    , m_StageEdge(false)
{
}

/*
 *  初期化
 */
void
IStageObject::
Initialize(const STAGE_OBJECT_ID& id, int x, int z)
{
    // アクティブフラグをON
    m_ActiveFlag = true;

    // コリジョンフラグをOFF
    m_CollisionFlag = false;

    //	座標設定
    m_Position = aqua::CVector3::ZERO;

    m_Position.x = x * m_default_size - m_default_size / 2.0f * 20.0f;

    m_Position.z = (20.0f - z) * m_default_size - m_default_size / 2.0f * 20.0f;

    
}

/*
 *  更新
 */
void
IStageObject::
Update(void)
{
    switch (m_ObjectState)
    {
    case IStageObject::GO_IN:   GoIn(); break;
    case IStageObject::PLAY:    break;
    case IStageObject::GO_OUT:  GoOut();break;
    default:
        break;
    }

    // アクティブフラグOFFなら終了
    if (!m_ActiveFlag)
        return;
}

/*
 *  描画
 */
void
IStageObject::
Draw(void)
{
    // アクティブフラグOFFなら終了
    if (!m_ActiveFlag)
        return;
    //m_Cube.Draw();
    m_Model.Draw();
}

/*
 *  解放
 */
void
IStageObject::
Finalize(void)
{
    // アクティブフラグをOFF
    m_ActiveFlag = false;
    m_Model.Unload();
}

/*
 *  ステージオブジェクトID取得
 */
STAGE_OBJECT_ID
IStageObject::
GetStageObjectID(void) const
{
    return m_StageObjectID;
}

/*
 *  ステージオブジェクトID設定
 */
void
IStageObject::
SetStageObjectID(STAGE_OBJECT_ID id)
{
    m_StageObjectID = id;
}

/*
 *  アクティブ状態チェック
 */
bool
IStageObject::
IsActive(void) const
{
    return m_ActiveFlag;
}

/*
 *  アクティブフラグ設定
 */
void
IStageObject::
SetActive(bool active)
{
    m_ActiveFlag = active;
}

bool IStageObject::CollisionCheck(aqua::CVector3 position, aqua::CVector3 destination, bool this_bullet)
{
    // 自身がnullなら偽を返す
    if (!this)
        return false;

    // キューブの判定を返す
    return m_Cube.CheckCollision(position, destination);
}

void IStageObject::GoIn(void)
{
    // 端なら処理しない
    if (m_StageEdge)
    {
        m_ObjectState = PLAY;
        return;
    }
    // positionの仮変数
    m_Model.position.y += 0.5f;
    // 完全に出たら状態を遷移
    if (m_Model.position.y > m_Position.y)
        m_ObjectState = PLAY;

}

void IStageObject::GoOut(void)
{
    // positionの仮変数
    m_Model.position.y -= 0.5f;

    // 完全に沈み切ったら終了
    if (m_Model.position.y < m_Cube.height)
        m_ObjectState = FINISH;
}
