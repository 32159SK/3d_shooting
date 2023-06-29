#include "../../../game_object.h"
#include "boss_cannon/boss_cannon.h"
#include "boss_enemy.h"

const float CBossEnemy::m_summon_interval = 15.0f;
const aqua::CVector3 CBossEnemy::m_base_fort_pos[] = { aqua::CVector3::ZERO,aqua::CVector3::ZERO };
const std::string CBossEnemy::m_model_file_path = "data\\model\\boss_enemy_N.mv1";


CBossEnemy::CBossEnemy(aqua::IGameObject* parent)
	: CEnemy(parent, "BossEnemy")
	, m_Phase(BOSS_PHASE::FIRST)
	, m_FortPos{ aqua::CVector3::ZERO }
	, m_Cannon{ nullptr }
	, m_EnemyManager{ nullptr }
{
}

void CBossEnemy::
Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m, CBulletManager* bm)
{
	CEnemy::Initialize(pop_pos, enemy_info, st_m, bm);
	m_Model.Load("data\\model\\fixed_enemy.mv1");
	m_Model.position = m_Position;
	m_ShotBullet = BULLET_TYPE::PENETRATE;
	m_Cube.visible = false;

	// 親(敵管理)クラスを取得
	m_EnemyManager = (CEnemyManager*)IGameObject::GetParent();

	m_SummonTimer.Setup(m_summon_interval);

	for (int i = 0; i < BOSS_PHASE::SECOND; i++)
		m_PhaseLife[i] = m_Life + m_Life / 2.0f * i;
	for (int i = 0; i < 2; ++i)
	m_Cannon[i] = (CBossCannon*)m_EnemyManager->CreateBossParts(m_base_fort_pos[i], ENEMY_ID::BOSS_CANNON);

}

void CBossEnemy::Update(void)
{
	IGameObject::Update();

	if (m_Player->GetTimeStop())
		return;


	m_ShotCT.Update();
	if (m_ShotCT.Finished())
	{
		Shot();
		m_ShotCT.Reset();
	}
	Move();

	m_Cube.m_HRotate = m_Rotate;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CBossEnemy::Draw(void)
{
	m_Model.Draw();
	CEnemy::Draw();
}

void CBossEnemy::Finalize(void)
{
	CEnemy::Finalize();
	m_Model.Unload();
}

bool CBossEnemy::CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)
{
	return false ;
}

void CBossEnemy::Shot(void)
{

	switch (m_Phase)
	{
	case CBossEnemy::FIRST:	m_ShotBullet = BULLET_TYPE::BOSS;

		break;
	case CBossEnemy::SECOND:m_ShotBullet = BULLET_TYPE::BEAM;

		break;
	default:
		break;
	}


}

void CBossEnemy::Move(void)
{
	switch (m_Phase)
	{
	case CBossEnemy::FIRST: FirstPhase();	break;
	case CBossEnemy::SECOND:SecondPhase();	break;
	case CBossEnemy::DEAD:  Dead();			break;
	default:
		break;
	}

}

void CBossEnemy::Damage(int damage)
{
	m_PhaseLife[m_Phase] -= damage;

	// 形態ごとのライフが0以下なら形態移行
	if (m_PhaseLife[m_Phase] <= 0)
		PhaseChange();
}

void CBossEnemy::Dead(void)
{
	m_DeadTimer.Update();
	m_DeadFlag = true;
	m_Cube.visible = false;
	m_EffectManager->Create(EFFECT_ID::DEAD, m_Position);
	// 死亡演出用タイマー
	if (m_DeadTimer.Finished())
		DeleteObject();
}

void CBossEnemy::FirstPhase(void)
{

	// プレイヤーと自身の距離
	aqua::CVector3 v = m_Player->GetPosition() - m_Position;

	// ベクトルのノーマライズ
	v.Normalize();

	// 2点から回転角度を求める
	m_Rotate = aqua::RadToDeg(atan2(v.x, v.z));
}

void CBossEnemy::SecondPhase(void)
{
	// タイマーの更新
	m_SummonTimer.Update();

	// 生成タイマーが終了
	if (m_SummonTimer.Finished())
		SummonEnemy();

}

void CBossEnemy::PhaseChange(void)
{
	// 自身の形態を次の形態へ変更
	m_Phase = (BOSS_PHASE)((int)m_Phase + 1);

	// モデルをアンロード
	m_Model.Unload();

	if (m_Phase != BOSS_PHASE::DEAD)
	{
		// 
		std::string model_path = m_model_file_path;

		model_path.replace(model_path.find("N"), 1, std::to_string((int)m_Phase + 1));

		m_Rotate = 0.0f;
		m_Model.Load(model_path);

		m_Model.position = m_Position;
	}
}

void CBossEnemy::SummonEnemy(void)
{
	// 雑魚を召喚
	m_EnemyManager->Create(m_FortPos[0], ENEMY_ID::MOB);
	m_EnemyManager->Create(m_FortPos[2], ENEMY_ID::MOB);
	m_SummonTimer.Reset();
}
