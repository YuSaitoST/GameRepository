/**
 * @file WireStrategy.h
 * @brief ƒƒCƒ„[‚ÌU‚é•‘‚¢‚ÌŠî’êƒNƒ‰ƒX
 * @author âV“¡—D‰F
 * @date 2021/05/14
 */

#pragma once

//‘O•ûéŒ¾
class ObjWire;

class WireStrategy {
public:
	WireStrategy() {}
	virtual ~WireStrategy() {}

	virtual void Update(ObjWire* wire) = 0;
};