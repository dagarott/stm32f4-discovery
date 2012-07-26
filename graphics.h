/**
  ******************************************************************************
  * @file    graphics.h
  * @author  Daniel Garcia
  * @version V1.0.0
  * @date    30-September-2011
  * @brief
  *
  *
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/** @addtogroup
  * @{
  */

/** @addtogroup
  * @{
  */

/* Includes ------------------------------------------------------------------*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _GRAPHICS_H_
#define GRAPHICS_H_

#define MENU_FIN                0
#define MENU_COMANDO            1
#define MENU_SUBMENU            2
#define SUBMENU_ANTERIOR        3
#define MENU_MAIN               4


typedef struct{
    UINT8 TipoMenu;
    const UINT8 *TextoMenu;
    UINT8 *Menu;
    void (*PtrFuncionSeleccion)(void);
    const UINT16 *PtrIcono;
}MENU;

const MENU MenuSubMenu1[];
const MENU MenuSubMenu2[];
const MENU MenuSubMenu3[];

// Declaración del menu principal, al seleccionar el boton inferior “Menu” ingresamos al ..
// .. submenu MenuSubMenu1
const MENU MenuPrincipal[]={
    {MENU_MAIN,"Menu Principal",(UINT8 *)&MenuSubMenu1,NULL,NULL},
    {MENU_FIN,"",NULL,NULL,NULL}
};
// Declaración del subMenu1. Al retroceder volvemos al principal indicado en el primer..
// .. ítem del arreglo. Luego se declara cada ítems.
const MENU MenuSubMenu1[]={
    {SUBMENU_ANTERIOR,"Sub Menu 1",(UINT8 *)&MenuPrincipal,NULL,NULL},
    {MENU_SUBMENU,"Sub Menu 2",(UINT8 *)&MenuSubMenu2,NULL,&Icono1[0]},
    {MENU_SUBMENU,"Juegos",(UINT8 *)&MenuSubMenu3,NULL,&Icono4[0]},
    {MENU_COMANDO,"About",NULL,vAbout,&Icono3[0]},
    {MENU_FIN,"",NULL,NULL,NULL}
};
// Declaración del subMenu2. Al retroceder volvemos al subMenu1 indicado en el primer..
// .. ítem del arreglo. Luego se declara cada ítems.
const MENU MenuSubMenu2[]={
    {SUBMENU_ANTERIOR,"Sub Menu 2",(UINT8 *)&MenuSubMenu1,NULL,NULL},
    {MENU_COMANDO,"Funcion",NULL,vModificarVariable,&Icono3[0]},
    {MENU_COMANDO,"Radio Buttons",NULL,vVisualizarRadioButtons,&Icono7[0]},
    {MENU_COMANDO,"Check Buttons",NULL,vVisualizarCheckButtons,&Icono7[0]},
    {MENU_FIN,"",NULL,NULL,NULL}
};
// Declaración del subMenu3. Al retroceder volvemos al subMenu1 indicado en el primer..
// .. ítem del arreglo. Luego se declara cada ítems.
const MENU MenuSubMenu3[]={
    {SUBMENU_ANTERIOR,"Juegos",(UINT8 *)&MenuSubMenu1,NULL,NULL},
    {MENU_COMANDO,"Simons Says",NULL,vJuegoSimonsSays,&Icono5[0]},
    {MENU_FIN,"",NULL,NULL,NULL}
};



#endif  /*_GRAPHICS_H_*/