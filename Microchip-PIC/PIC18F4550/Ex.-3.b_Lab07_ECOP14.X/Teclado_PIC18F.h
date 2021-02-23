// -----------------------------------------------------------------------
//   Arquivo: Teclado_PIC18F.h
//            
//   Autor:   Pabllo Lins
//	 Data: 17/02/2021
//	 Baseado na biblioteca das informações dos comentários abaixo
//
// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2010
// -----------------------------------------------------------------------
//   Arquivo: keypad.h
//            Header da biblioteca de operação de um teclado matricial
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licença: GNU GPL 2
// -----------------------------------------------------------------------
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; version 2 of the License.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// -----------------------------------------------------------------------

#ifndef TECLADO_PIC18F_H
	#define TECLADO_PIC18F_H

	unsigned char LeituraTeclado(void);
	void DebounceTeclado(void);
	void IniciaTeclado(void);

#endif