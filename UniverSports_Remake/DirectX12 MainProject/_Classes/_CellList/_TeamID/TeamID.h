#pragma once

#include "DontDestroyOnLoad.h"

class TeamID {
public:
	TeamID() : id_(-1) {}
	virtual ~TeamID() {}

	void Set(const int teamID) { id_ = teamID; }
	int Get() const { return id_; }
	static int Get(const int playerID) { return DontDestroy->TeamID[playerID]; }

private:
	int id_;
};