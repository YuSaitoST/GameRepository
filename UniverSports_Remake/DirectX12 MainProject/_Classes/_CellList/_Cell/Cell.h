#pragma once

class ObjectBase;

// ��ԃN���X
class Cell {
public:
	Cell();
	Cell(ObjectBase* m);
	virtual ~Cell();

	void UpdateToMorton();		// mp_�ɍ��킹�ă��[�g���������X�V����
	void Remove();				// �o�������X�g���甲����
	ObjectBase* GetCollision();  // �Փ˔���

	// �o�������X�g(�����̑O��̋�Ԃ�����)
	Cell* prev_;
	Cell* next_;

	ObjectBase* mp_;  // �������镨��

	int level_;	    // ��ԃ��x��
	int LsIndex_;   // �e���x���ł�Index
	int MsIndex_;   // ���`�l���؂ɂ�����Index

private:
	ObjectBase* UpperSearch();		  // ��ʒT��
	ObjectBase* LowerSearch(int nr);  // ���ʒT��

	static void MoverToMorton(ObjectBase& m, int& L, int& I, int& M);
};