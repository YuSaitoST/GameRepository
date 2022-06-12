/**
 * @file AtEndCondition.h
 * @brief ƒQ[ƒ€‚ÌI—¹ğŒ‚ÌŠî’êƒNƒ‰ƒX
 * @author âV“¡—D‰F
 * @date 2021/06/04
 */

#pragma once

//‘O•ûéŒ¾
class CountTimer;

class AtEndCondition {
public:
	AtEndCondition() {}
	virtual ~AtEndCondition() {}

	virtual bool IsFined(CountTimer* timer) = 0;
};