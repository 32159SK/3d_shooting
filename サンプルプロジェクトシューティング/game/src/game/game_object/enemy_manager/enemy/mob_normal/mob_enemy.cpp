#include "../../../game_object.h"
#include "mob_enemy.h"

const float CMobEnemy::m_follow_range = 100.0f;
const float CMobEnemy::m_lose_sight_time = 2.0f;
const float CMobEnemy::m_turning_speed = 2.0f;


CMobEnemy::CMobEnemy(aqua::IGameObject* parent)
	: CEnemy(parent,"MobEnemy")
	, m_Follow(false)
{
}

void
CMobEnemy::
Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m, CBulletManager* bm)
{
	// モデルのロード
	m_Model.Load("data\\model\\mob_enemy.mv1");
	// タイマーのセットアップ
	m_LoseSightTimer.Setup(m_lose_sight_time);
	// 最初の向きを乱数で決める
	m_Dir = m_surroundings[aqua::Rand(3)];
	m_ShotBullet = BULLET_TYPE::NORMAL;

	// 基本的なユニットの初期化を基底クラスの初期化を呼び出して行う
	CEnemy::Initialize(pop_pos, enemy_info, st_m, bm);
}

void CMobEnemy::Shot(void)
{
	// 追尾していないなら撃たない
	if (!m_Follow)
		return;

	CEnemy::Shot();
}

void CMobEnemy::Move(void)
{
	// 追尾しているか否かで処理を分ける
	if (FollowCheck())
		Follow();
	else
		NotFollow();
}

void CMobEnemy::Follow(void)
{
	// 見失ったら追跡を解除
	if (m_LoseSightTimer.Finished())
	{
		m_Follow = false;
		m_LoseSightTimer.Reset();
		return;
	}
	// デルタタイム取得
	const float to_delta = 60.0f * aqua::GetDeltaTime();
	aqua::CVector3 player_pos = m_Player->GetAgoPos();

	// プレイヤーと自身の距離
	aqua::CVector3 v = player_pos - m_Position;

	float dir = aqua::CVector2::Cross(aqua::CVector2(v.x, v.z), aqua::CVector2(m_Velocity.x, m_Velocity.z));

	// プレイヤーにいる方へ向く
	if (dir > 0.001f)
		m_Angle -= aqua::DegToRad(m_turning_speed);
	else if (dir < 0.001f)
		m_Angle += aqua::DegToRad(m_turning_speed);

	m_Velocity.x = (m_Speed * to_delta) * cos(m_Angle);
	m_Velocity.z = (m_Speed * to_delta) * sin(m_Angle);

	// 壁と当たってたらそこで止まる(ついでに見失うまでのカウントを進める)
	if (m_StageManager->StageObjectCollision(m_Position, m_Position + m_Velocity * m_Width * 1.5f,false))
	{
		m_LoseSightTimer.Update();
		return;
	}
	CEnemy::Move();
}

void CMobEnemy::NotFollow(void)
{
	const float to_delta = 60.0f * aqua::GetDeltaTime();
	
	// 壁に当たったら向きを変える
	if (m_StageManager->StageObjectCollision(m_Position, m_Position + m_Velocity * m_Width * 1.5f, false))
		m_Dir = m_surroundings[aqua::Rand(3)];

	m_Velocity.x = (m_Speed * to_delta) * m_Dir.x;
	m_Velocity.z = (m_Speed * to_delta) * m_Dir.z;

	CEnemy::Move();
}

bool CMobEnemy::FollowCheck(void)
{
	if (m_Follow)
		return true;
	// プレイヤーと自身の距離
	aqua::CVector3 v = m_Player->GetPosition() - m_Position;

	// 範囲内かつ、壁を隔てていないなら追跡開始
	if (m_follow_range > abs(aqua::CVector3::Length(v)) && !m_StageManager->StageObjectCollision(m_Player->GetPosition(), m_Position, false))
		m_Follow = true;
	else
		m_Follow = false;

	return m_Follow;
}
