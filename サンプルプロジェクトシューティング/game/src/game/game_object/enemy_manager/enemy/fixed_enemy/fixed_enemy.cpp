#include "../../../game_object.h"
#include "fixed_enemy.h"

const float CFixedEnemy::m_capture_range = 200.0f;

CFixedEnemy::CFixedEnemy(aqua::IGameObject* parent)
	: CEnemy(parent, "FixedEnemy")
	, m_Capture(false)
{
}

void CFixedEnemy::
Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m, CBulletManager* bm)
{
	// モデルのロード
	m_Model.Load("data\\model\\fixed_enemy.mv1");

	// 撃つ弾種の設定
	m_ShotBullet = BULLET_TYPE::BEAM;

	// 基本的なユニットの初期化を基底クラスの初期化を呼び出して行う
	CEnemy::Initialize(pop_pos, enemy_info, st_m, bm);
}

void CFixedEnemy::Update(void)
{
	CEnemy::Update();
	m_Cube.m_HRotate = m_Rotate;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CFixedEnemy::Shot(void)
{
	// 捕捉していれば射撃
	if (m_Capture)
		CEnemy::Shot();
}

void CFixedEnemy::Move(void)
{
	// プレイヤーと自身の距離
	aqua::CVector3 v = m_Player->GetPosition() - m_Position;

	// 一度でも捕捉すれば死ぬまでこちらを向く
	if (m_capture_range > abs(aqua::CVector3::Length(v)))
		m_Capture = true;
	else if (!m_Capture)
		return;

	// ベクトルのノーマライズ
	v.Normalize();

	// 2点から回転角度を求める
	m_Rotate = aqua::RadToDeg(atan2(v.x, v.z));
}
