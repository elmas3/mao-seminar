/*==================================
	
	[Sprite.h]
	�X�v���C�g�`�揈��
	Author : �o���đ�

=================================*/

#pragma once
#include "main.h"

//Sprite�N���X
class Sprite
{
public:
	D3DCOLOR SetColor(int r, int g, int b, int a);	//	�J���[�̐ݒ�
	//	�`�� (�����F�e�N�X�`���AX���W�AY���W�A�e�N�X�`��X���W�A�e�N�X�`��Y���W�A�e�N�X�`���̉����A�e�N�X�`���̏c��)
	void Draw(LPDIRECT3DTEXTURE9 Texture, float dx, float dy, float Width, float Height, D3DXCOLOR Color = D3DCOLOR_RGBA(255, 255, 255, 255));
	//	�`�� (�����F�e�N�X�`���AX���W�AY���W�A�e�N�X�`���̉����A�e�N�X�`���̏c���A�e�N�X�`��X���W�A�e�N�X�`��Y���W�A�`�悷�鉡���A�`�悷��c��)
	void Draw(LPDIRECT3DTEXTURE9 Texture, float dx, float dy, float Width, float Height, float tx, float ty, float tw, float th, D3DXCOLOR Color = D3DCOLOR_RGBA(255, 255, 255, 255));
	//	�`�� (�����F�e�N�X�`���AX���W�AY���W�A�e�N�X�`��X���W�A�e�N�X�`��Y���W�A�e�N�X�`���̉����A�e�N�X�`���̏c���A�e�N�X�`���̒��S���W�A�g��k���A��])
	void Draw(LPDIRECT3DTEXTURE9 Texture, float dx, float dy, float Width, float Height, float tx, float ty, float tw, float th, float cx, float cy, float sx, float sy, float rotation, D3DXCOLOR Color = D3DCOLOR_RGBA(255, 255, 255, 255));
};
