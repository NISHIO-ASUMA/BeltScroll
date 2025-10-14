//=====================================
//
// �����L���O�V�[������ [ ranking.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _RANKING_H_ // ���̃}�N����`������ĂȂ�������
#define _RANKING_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �C���N���[�h�t�@�C���錾
//******************************
#include "scene.h"
#include "rankingscore.h"

//******************************
// �����L���O�V�[���N���X���`
//******************************
class CRanking : public CScene
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CRanking();
	~CRanking();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetSort(void);
	void TxtLoad(const char* pFileName);
	void TxtSave(const char* pFileName);

	// �ÓI�����o�֐�
	static CRanking* Create();

private:
	static constexpr int MAX_RANK = 5;
	static constexpr int MAX_RANKTEX = 2;

	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_RANKTEX];		// �e�N�X�`���̃|�C���^
	static CRankingScore* m_Score[MAX_RANK];

	CNumber* m_apNumbers[8];								// �����̃|�C���^
	int m_nNumData[MAX_RANK];								// �����̃f�[�^��
};

#endif