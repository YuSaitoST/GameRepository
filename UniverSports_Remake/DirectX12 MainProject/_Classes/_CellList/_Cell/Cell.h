#pragma once

class ObjectBase;

// 空間クラス
class Cell {
public:
	Cell();
	Cell(ObjectBase* m);
	virtual ~Cell();

	void UpdateToMorton();		// mp_に合わせてモートン符号を更新する
	void Remove();				// 双方向リストから抜ける
	ObjectBase* GetCollision();  // 衝突判定

	// 双方向リスト(自分の前後の空間を入れる)
	Cell* prev_;
	Cell* next_;

	ObjectBase* mp_;  // 所属する物体

	int level_;	    // 空間レベル
	int LsIndex_;   // 各レベルでのIndex
	int MsIndex_;   // 線形四分木におけるIndex

private:
	ObjectBase* UpperSearch();		  // 上位探索
	ObjectBase* LowerSearch(int nr);  // 下位探索

	static void MoverToMorton(ObjectBase& m, int& L, int& I, int& M);
};