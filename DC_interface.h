/*
 * DC_interface.h
 *
 *  Created on: Feb 22, 2022
 *      Author: shady
 */

#ifndef DC_INTERFACE_H_
#define DC_INTERFACE_H_

#define FORWARD     0
#define BACKWARD 	1
#define LEFT		2
#define RIGHT		3
#define STOP        4




void DC_EN1();
void DC(uint8 Copy_Direction);

#endif /* DC_INTERFACE_H_ */
