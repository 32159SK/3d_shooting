
/*!
 *  @file       game.cpp
 *  @brief      ゲーム管理
 *  @author     Kazuya Maruyama
 *  @date       2021/02/06
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "game.h"
#include "game_object/game_object.h"

const unsigned int CGame::m_clear_color = 0xff7f7f7f;

/*
 *  コンストラクタ
 */
CGame::
CGame( aqua::IGameObject* parent )
    : aqua::IGameObject( parent, "Game" )
{
}

/*
 *  初期化
 */
void
CGame::
Initialize(void)
{
    // 最初に作るオブジェクト群
    // サウンド管理クラス
    aqua::CreateGameObject<CSoundManager>(this);
    aqua::CreateGameObject<CSceneManager>(this);
    // シーンを跨いでデータの共有を行う中継クラス
    aqua::CreateGameObject<CDataRelay>(this);
    // マウスの描画を行う
    SetMouseDispFlag(true);


    IGameObject::Initialize();
}

/*
 *  描画
 */
void
CGame::
Draw(void)
{
    // 画面のクリア
    aqua::Clear(m_clear_color);

    // 描画したいオブジェクト群

    IGameObject::Draw();
}
