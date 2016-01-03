#include <stdio.h>
#include <graphics.h>
#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

#define PI 3.14159
#define MaxInimigos 70
#define MaxX 900
#define MaxY 700
#define TempoTiroBoss 20
#define TempoTiro 15
#define TempoInimigo 10 
#define tRespawn 30 
#define ESC 27
#define A 65
#define D 68
#define CTRL 17
#define P_Fundo "../GuerraMundial/Imagens/Background.jpg"
#define P_Player_M "../GuerraMundial/Imagens/Player_M.jpg"
#define P_Player1 "../GuerraMundial/Imagens/Player1.jpg"
#define P_Player2 "../GuerraMundial/Imagens/Player2.jpg"
#define P_Tiro_M "../GuerraMundial/Imagens/Tiro_M.jpg"
#define P_Shoot "../GuerraMundial/Imagens/Tiro.jpg"
#define P_I1_M "../GuerraMundial/Imagens/I1_M.jpg"
#define P_I1 "../GuerraMundial/Imagens/I1.jpg"
#define P_I2_M "../GuerraMundial/Imagens/I2_M.jpg"
#define P_I2 "../GuerraMundial/Imagens/I2.jpg"
#define P_I3_M "../GuerraMundial/Imagens/I1_M.jpg"
#define P_I3 "../GuerraMundial/Imagens/I3.jpg"
#define P_Boss_M "../GuerraMundial/Imagens/Boss_M.jpg"
#define P_Boss "../GuerraMundial/Imagens/Boss.jpg"
#define P_BossT "../GuerraMundial/Imagens/TiroChefe.jpg"
#define P_BossT_M "../GuerraMundial/Imagens/TiroChefe_M.jpg"
#define P_VidaP "../GuerraMundial/Imagens/Vida.jpg"
#define P_VidaP_M "../GuerraMundial/Imagens/Vida_M.jpg"
#define P_VidaT "../GuerraMundial/Imagens/VidaT.jpg"
#define P_VidaT_M "../GuerraMundial/Imagens/VidaT_M.jpg"
#define P_StartB "../GuerraMundial/Imagens/Jogar.jpg"
#define P_StartB_M "../GuerraMundial/Imagens/Jogar_M.jpg"
#define P_SairB "../GuerraMundial/Imagens/Sair.jpg"
#define P_SairB_M "../GuerraMundial/Imagens/Sair_M.jpg"
#define P_Cena1 "../GuerraMundial/Imagens/Cena1.jpg"
#define P_Cena2 "../GuerraMundial/Imagens/Cena2.jpg"
#define P_Final "../GuerraMundial/Imagens/Final.jpg"
#define P_GameOver "../GuerraMundial/Imagens/FimTexto.jpg"
#define P_GameOver_M "../GuerraMundial/Imagens/FimTexto_M.jpg"

int i, j, k, v, t, xmouse, ymouse , xbotao, ybotao, status, VidaPlayer , VidaTerra , contInimigos, noInimigos,
	Tam_F, Tam_P, Tam_T, Tam_TM, Tam_I, Tam_IM, Tam_B, Tam_BM, Tam_VP, Tam_VT, Tam_BT, Tam_C1, Tam_C2, Tam_Final, Tam_TB, Tam_Texto;
int tempoDecorrido, timer1 , timer2 , timerInimigo , timerRespawn , timerBoss;
char *Cont, *Texto;
void *F, *PM, *P1, *P2, *TM, *T, *I1_M, *I1, *I2_M, *I2, *I3_M, *I3, *B, *BM, *TB, *TB_M, *VP, *VP_M, *VT, *VT_M, *BT_JM, *BT_SM, *BT_J, *BT_S, *C1, *C2, *Final, *G, *GM;

int Jogo();
int Cena1();
int Cena2();
int CenaFinal();
int CenaGameOver();
int CarregaImagens();
int IniciaVarJog();
int IniciaVarJogo();
int IniciaVarInim();
int DesenhaFundo();
int DesenhaPlayer1();
int DesenhaPlayer2();
int MovePlayer1();
int MovePlayer2();
int DesenhaVidaP();
int DesenhaVidaT();
int MoveTiro(); 
int ExecutaTiro();
int InicializaInimigos();
int Chefao();
int DesenhaBoss();
int ContadorInimigos();
int colisaoTiro();
int colisaoBossTiro();
int colisaoJog1();
int colisaoJog2();
int Inim1();
int Inim2();
int Inim3();
int GameOver();


struct TPlayer
{
	int x, y, passo, situacao, distx, disty;
};
TPlayer Player[2];

struct TTiro
{
	int x, y, situacao, passo, distx, disty;
};
TTiro Tiro1[10];
TTiro Tiro2[10];

struct TInimigos
{
	int x, y, situacao, passo, tipo;
};
TInimigos Inimigos[MaxInimigos];

struct TBoss
{
	int x, y, situacao, passoy, passox, vida;	
};
TBoss Boss[1];

struct TTiroBoss
{
	int x, y, situacao, passo;
};
TTiroBoss TiroBoss[5];

int main()
{
	srand(time(NULL));
	status = 1;
	initwindow(MaxX, MaxY);
	
	IniciaVarJogo();
	IniciaVarJog();
	IniciaVarInim();
	CarregaImagens();
	
	while(status != 0)
	{
		if(status == 1)	Jogo();
		else if(status == 2)CenaFinal();
		else if(status == 3)CenaGameOver();

	}
	closegraph();
	return 0;
}

// CARREGA TODOS OS SPRITES UTILIZADOS NO PROGRAMA
int CarregaImagens()
{
	readimagefile(P_Fundo, 0, 0, MaxX, MaxY);
	Tam_F = imagesize(0, 0, MaxX, MaxY);
	F = malloc(Tam_F);
	getimage(0, 0, MaxX, MaxY, F);
	
	readimagefile(P_Cena1, 0, 0, MaxX, MaxY);
	Tam_C1 = imagesize(0, 0, MaxX, MaxY);
	C1 = malloc(Tam_C1);
	getimage(0, 0, MaxX, MaxY, C1);
	
	readimagefile(P_Cena2, 0, 0, MaxX, MaxY);
	Tam_C2 = imagesize(0, 0, MaxX, MaxY);
	C2 = malloc(Tam_C2);
	getimage(0, 0, MaxX, MaxY, C2);

	readimagefile(P_Final, 0, 0, MaxX, MaxY);
	Tam_Final = imagesize(0, 0, MaxX, MaxY);
	Final = malloc(Tam_Final);
	getimage(0, 0, MaxX, MaxY, Final);

	
	readimagefile(P_Player_M, 0, 0, 54, 44);
	Tam_P = imagesize(0, 0, 54, 44);
	PM = malloc(Tam_P);
	getimage(0, 0, 54, 44, PM);

	readimagefile(P_Player1, 90, 0, 144, 44);
	P1 = malloc(Tam_P);
	getimage(90, 0, 144, 44, P1);
	
	readimagefile(P_Player2, 180, 0, 234, 44);
	P2 = malloc(Tam_P);
	getimage(180, 0, 234, 44, P2);
	
	readimagefile(P_Tiro_M, 0, 40, 10, 55);
	Tam_TM = imagesize(0, 0, 10, 15);
	TM = malloc(Tam_TM);
	getimage(0, 40, 10, 55, TM);
	
	readimagefile(P_Shoot, 30, 40, 40, 55);
	Tam_T = imagesize(0, 0, 10, 15);
	T = malloc(Tam_T);
	getimage(30, 40, 40, 55, T);
	
	readimagefile(P_I1_M, 0, 0, 64, 54);
	Tam_IM = imagesize(0, 0, 64, 54);
	I1_M = malloc(Tam_IM);
	getimage(0, 0, 64, 54, I1_M);
	
	readimagefile(P_I1, 90, 0, 154, 54);
	I1 = malloc(Tam_IM);
	getimage(90, 0, 154, 54, I1);
	
	readimagefile(P_I2_M, 0, 0, 64, 54);
	Tam_IM = imagesize(0, 0, 64, 54);
	I2_M = malloc(Tam_IM);
	getimage(0, 0, 64, 54, I2_M);
	
	readimagefile(P_I2, 90, 0, 154, 54);
	I2 = malloc(Tam_IM);
	getimage(90, 0, 154, 54, I2);
	
	readimagefile(P_I3_M, 0, 0, 64, 54);
	Tam_IM = imagesize(0, 0, 64, 54);
	I3_M = malloc(Tam_IM);
	getimage(0, 0, 64, 54, I3_M);
	
	readimagefile(P_I3, 90, 0, 154, 54);
	I3 = malloc(Tam_IM);
	getimage(90, 0, 154, 54, I3);	
	
	readimagefile(P_Boss_M, 0, 0, 200, 160);
	Tam_BM = imagesize(0, 0, 200, 160);
	BM = malloc(Tam_BM);
	getimage(0, 0, 200, 160, BM);
	
	readimagefile(P_Boss, 110, 0, 310, 160);
	Tam_B = imagesize(0, 0, 200, 160);
	B = malloc(Tam_B);
	getimage(110, 0, 310, 160, B);
	
	readimagefile(P_VidaP, 0, 0, 20, 20);
	Tam_VP = imagesize(0, 0, 20, 20);
	VP = malloc(Tam_VP);
	getimage(0, 0, 20, 20, VP);
	
	readimagefile(P_VidaP_M, 20, 0, 40, 20);
	VP_M = malloc(Tam_VP);
	getimage(20, 0, 40, 20, VP_M);
	
	readimagefile(P_VidaT, 0, 0, 20, 20);
	Tam_VT = imagesize(0, 0, 20, 20);
	VT = malloc(Tam_VT);
	getimage(0, 0, 20, 20, VT);
	
	readimagefile(P_VidaT_M, 20, 0, 40, 20);
	VT_M = malloc(Tam_VT);
	getimage(20, 0, 40, 20, VT_M);

	readimagefile(P_StartB, 0, 0, 140, 140);
	Tam_BT = imagesize(0, 0, 140, 140);
	BT_J = malloc(Tam_BT);
	getimage(0, 0, 140, 140, BT_J);
	
	readimagefile(P_StartB_M, 140, 0, 280, 140);
	BT_JM = malloc(Tam_BT);
	getimage(140, 0, 280, 140, BT_JM);
		
	readimagefile(P_SairB, 0, 0, 140, 140);
	BT_S = malloc(Tam_BT);
	getimage(0, 0, 140, 140, BT_S);
	
	readimagefile(P_SairB_M, 140, 0, 280, 140);
	BT_SM = malloc(Tam_BT);
	getimage(140, 0, 280, 140, BT_SM);
	
	readimagefile(P_BossT, 0, 0, 30, 30);
	Tam_TB = imagesize(0, 0, 30, 30);
	TB = malloc(Tam_TB);
	getimage(0, 0, 30, 30, TB);
	
	readimagefile(P_BossT_M, 30, 0, 60, 30);
	TB_M = malloc(Tam_TB);
	getimage(30, 0, 60, 30, TB_M);	
	
	readimagefile(P_GameOver, 0, 0, MaxX, 300);
	Tam_Texto = imagesize(0, 0, MaxX, 300);
	G = malloc(Tam_Texto);
	getimage(0, 0, MaxX, 300, G);
	
	readimagefile(P_GameOver_M, 0, 300, MaxX, 600);
	GM = malloc(Tam_Texto);
	getimage(0, 300, MaxX, 600, GM);
}

// Inicia algumas variáveis do jogo
int IniciaVarJogo()
{
	VidaPlayer = 5;
	VidaTerra = 10;
	contInimigos = 0;
	timer1 = 0;
	timer2 = 0;
	timerInimigo = 0;
	timerRespawn = 0;
	timerBoss = 0;
}



// Inicializa as variáveis dos jogadores e dos tiros
int IniciaVarJog()
{
	Player[0].x = 700;
	Player[0].y = MaxY - 60;
	Player[0].situacao = 1;
	Player[0].passo = 6;
	
	Player[1].x = 10;
	Player[1].y = MaxY - 60;
	Player[1].situacao = 1;
	Player[1].passo = 6;
	
	for(j = 0; j < 10; j++)
	{
		Tiro1[j].x = Player[0].x + 40;
		Tiro1[j].y = -50;
		Tiro1[j].situacao = 0;
		Tiro1[j].passo = 7;
	}
	
	for(j = 0; j < 10; j++)
	{
		Tiro2[j].x = Player[1].x + 40;
		Tiro2[j].y = -50;
		Tiro2[j].situacao = 0;
		Tiro2[j].passo = 7;
	}
	
}

//INICIALIZA AS VARIÃVEIS DOS INIMIGOS
int IniciaVarInim()
{
	for(i = 0; i < MaxInimigos; i++)
	{
		Inimigos[i].x = rand() % 800;
		Inimigos[i].y = -(rand() % 4000 + 200) ;
		Inimigos[i].situacao = 1;
		Inimigos[i].tipo = rand() % 3;
		Inimigos[i].passo = 5;
	}
	
	Boss[0].x = 350;
	Boss[0].y = -200;
	Boss[0].situacao = 0;
	Boss[0].passoy = 50;
	Boss[0].passox = 4;
	Boss[0].vida = 15;	
}

// BACKGROUND
int DesenhaFundo()
{
	putimage(0, 0, F, COPY_PUT);	
}

// PRINTA O PLAYER 1 NA TELA
int DesenhaPlayer1()
{
	if(Player[0].situacao == 1)
	{
		putimage(Player[0].x, Player[0].y, PM, AND_PUT);
		putimage(Player[0].x, Player[0].y, P1, OR_PUT);
	}
}

//PRINTA O PLAYER 2 NA TELA
int DesenhaPlayer2()
{
	if(Player[1].situacao == 1)
	{
		putimage(Player[1].x, Player[1].y, PM, AND_PUT);
		putimage(Player[1].x, Player[1].y, P2, OR_PUT);
	}
}

// CONTROLES DO PLAYER 1/ DETECÃ‡ÃƒO DAS BORDAS
int MovePlayer1()
{
	if(GetKeyState(VK_RIGHT)&0x80) Player[0].x = Player[0].x + Player[0].passo;	
	if(GetKeyState(VK_LEFT)&0x80) Player[0].x = Player[0].x - Player[0].passo;
	
	if(Player[0].x <= 0) Player[0].x = 0;
	if(Player[0].x >= (MaxX - 70)) Player[0].x = MaxX - 70;
}

// CONTROLES DO PLAYER 2/ DESTECÃ‡ÃƒO DAS BORDAS
int MovePlayer2()
{
	if(GetKeyState(D)&0x80) Player[1].x = Player[1].x + Player[1].passo;	
	if(GetKeyState(A)&0x80) Player[1].x = Player[1].x - Player[1].passo;
	
	if(Player[1].x <= 0) Player[1].x = 0;
	if(Player[1].x >= (MaxX - 70)) Player[1].x = MaxX - 70;
}

// PRINTA OS TIROS NA TELA
int MoveTiro()
{
	for(j = 0; j < 10; j++)
	{
		if(Tiro1[j].situacao == 1)
		{
			putimage(Tiro1[j].x, Tiro1[j].y, TM, AND_PUT);
			putimage(Tiro1[j].x, Tiro1[j].y, T, OR_PUT);
			Tiro1[j].y = Tiro1[j].y - Tiro1[j].passo;
		}
		
	}
	
	for(j = 0; j < 10; j++)
	{
		if(Tiro2[j].situacao == 1)
		{
			putimage(Tiro2[j].x, Tiro2[j].y, TM, AND_PUT);
			putimage(Tiro2[j].x, Tiro2[j].y, T, OR_PUT);
			Tiro2[j].y = Tiro2[j].y - Tiro2[j].passo;
		}
		
	}
	
}

// PRINTA OS INIMIGOS NA TELA
int InicializaInimigos()
{

	for(i = 0; i < MaxInimigos; i++)
	{
		if(Inimigos[i].situacao == 1)
		{
			if(Inimigos[i].tipo == 0) Inim1();
			else if(Inimigos[i].tipo == 1) Inim2();
			else Inim3();
			
			Inimigos[i].y = Inimigos[i].y + Inimigos[i].passo;
		
		}
	}
}

int Chefao()
{
	if(contInimigos >= MaxInimigos) Boss[0].situacao = 1;
	
	
		if(Boss[0].situacao == 1)
		{
			DesenhaBoss(); 
			
			if(Boss[0].y < 0)
			{
				Boss[0].y += Boss[0].passoy;
			}
			else
			{
				Boss[0].x += Boss[0].passox;	
				
				if(Boss[0].x < 0 || Boss[0].x > 700)
				{
					Boss[0].passox = -Boss[0].passox;
					Boss[0].y += Boss[0].passoy;
				}
			}
		}	
}

int DesenhaBoss()
{
			
		putimage(Boss[0].x, Boss[0].y, BM, AND_PUT);
		putimage(Boss[0].x, Boss[0].y, B, OR_PUT);
		
}
	


// TIPOS DE INIMIGO
int Inim1()
{
	putimage(Inimigos[i].x, Inimigos[i].y, I1_M, AND_PUT);
	putimage(Inimigos[i].x, Inimigos[i].y, I1, OR_PUT);
}
int Inim2()
{
	putimage(Inimigos[i].x, Inimigos[i].y, I2_M, AND_PUT);
	putimage(Inimigos[i].x, Inimigos[i].y, I2, OR_PUT);
}
int Inim3()
{
	putimage(Inimigos[i].x, Inimigos[i].y, I3_M, AND_PUT);
	putimage(Inimigos[i].x, Inimigos[i].y, I3, OR_PUT);
}

//DETECTA SE O TIRO ACERTOU O INIMIGO
int colisaoTiro()
{
	i = MaxInimigos - 1;
    noInimigos = 0;

    while(noInimigos != 1 && i >= 0) 
	{
		j = 10;
		while(noInimigos != 1 && j >= 0)
		{
			Tiro1[j].distx = Tiro1[j].x - Inimigos[i].x;
			Tiro1[j].disty = Tiro1[j].y - Inimigos[i].y;
			if (Inimigos[i].situacao == 1 && Tiro1[j].situacao == 1 && (Tiro1[j].distx >= 10 && Tiro1[j].distx <= 100) && (Tiro1[j].disty >= 0 && Tiro1[j].disty <= 50) )
			{
    		
    			Tiro1[j].situacao = 0;
				Inimigos[i].situacao = 0;
    			noInimigos = 1;
    			contInimigos++;
			}
			j--;
		}		
		i--;
	}		

	i = MaxInimigos - 1;
    noInimigos = 0;

    while(noInimigos != 1 && i >= 0) 
	{
		k = 10;
		while(noInimigos != 1 && k >= 0)
		{
			Tiro2[k].distx = Tiro2[k].x - Inimigos[i].x;
			Tiro2[k].disty = Tiro2[k].y - Inimigos[i].y;
			if (Inimigos[i].situacao == 1 && Tiro2[k].situacao == 1 && (Tiro2[k].distx >= 10 && Tiro2[k].distx <= 100) && (Tiro2[k].disty >= 0 && Tiro2[k].disty <= 50) )
			{
    		
    			Tiro2[k].situacao = 0;
				Inimigos[i].situacao = 0;
    			noInimigos = 1;
    			contInimigos++;
			}
			k--;
		}		
		i--;
	}		
}

int colisaoBossTiro()
{
	noInimigos = 0;
	j = 10;
	while(noInimigos != 1 && j >= 0)
	{
		Tiro1[j].distx = Tiro1[j].x - Boss[0].x;
		Tiro1[j].disty = Tiro1[j].y - Boss[0].y;
		if (Boss[0].situacao == 1 && Tiro1[j].situacao == 1 && (Tiro1[j].distx >= 20 && Tiro1[j].distx <= 180) && (Tiro1[j].disty >= 0 && Tiro1[j].disty <= 140) )
		{
	    	
	   		Tiro1[j].situacao = 0;
			Boss[0].vida--;
	   		noInimigos = 1;
		}
		j--;
	}		
	
	noInimigos = 0;
	k = 10;
	while(noInimigos != 1 && k >= 0)
	{
		Tiro2[k].distx = Tiro2[k].x - Boss[0].x;
		Tiro2[k].disty = Tiro2[k].y - Boss[0].y;
		if (Boss[0].situacao == 1 && Tiro2[k].situacao == 1 && (Tiro2[k].distx >= 20 && Tiro2[k].distx <= 180) && (Tiro2[k].disty >= 0 && Tiro2[k].disty <= 140) )
		{
   			Tiro2[k].situacao = 0;
			Boss[0].vida--;
   			noInimigos = 1;
		}
		k--;
	}		
	
}
// DETECTA COLISÃƒO ENTRE JOGADOR/INIMIGO
int colisaoJog1()
{
	i = MaxInimigos - 1;
	noInimigos = 0;
	
	while(noInimigos != 1 && i >= 0)
	{
		j = 2;
		while(noInimigos !=1 &&  j >= 0)
		{
			Player[j].distx = Player[j].x - Inimigos[i].x;
			Player[j].disty = Player[j].y - Inimigos[i].y;
			if(Inimigos[i].situacao == 1 && Player[j].situacao == 1 && (Player[j].distx >= 5 && Player[j].distx <= 50) && (Player[j].disty >= 0 && Player[j].disty <= 20) )
			{
				Player[j].x = -200;
				Player[j].situacao = 0;
				Inimigos[i].situacao = 0;
				noInimigos = 1;
				timerRespawn = 0;
				VidaPlayer--;
			}
			j--;
		}
		i--;			
	}
} 

// DETECTA COLISÃƒO ENTRE INIMIGO/CENARIO
int colisaoTerra()
{
	i = MaxInimigos - 1;
	noInimigos = 0;
	
	while(noInimigos != 1 && i >= 0)
	{
		while(noInimigos !=1)
		{
			if(Inimigos[i].situacao == 1 && (Inimigos[i].y > MaxY) )
			{
				Inimigos[i].situacao = 0;
				noInimigos = 1;
				VidaTerra--;
			}
		}
		i--;			
	}
} 


// DETECTA O COMANDO PARA ATIRAR
int ExecutaTiro()
{
	if(Player[0].situacao == 1)
	{
		if(GetKeyState(VK_SPACE)&0x80)
		{
			for(i = 0; i < 10; i++)
			{	
				cout << "Tiro[" << i << "]  = " << Tiro1[i].situacao << endl;
				if (Tiro1[i].situacao == 0 && timer1 > TempoTiro)
				{
					Tiro1[i].situacao = 1;
					Tiro1[i].x = Player[0].x + 23;
					Tiro1[i].y = Player[0].y;
					timer1 = 0;
				}
			}
		}
	}
	
	if(Player[1].situacao == 1)
	{
		if(GetKeyState(CTRL)&0x80)
		{
			for(i = 0; i < 10; i++)
			{
				if (Tiro2[i].situacao == 0 && timer2 > TempoTiro)
				{
					Tiro2[i].situacao = 1;
					Tiro2[i].x = Player[1].x + 23;
					Tiro2[i].y = Player[1].y;
					timer2 = 0;
				}
			}
		}		
	}
}

//DESENHA VIDA DOS PLAYERS
int DesenhaVidaP()
{
	for(v = 0; v < VidaPlayer; v++)
	{
	
		putimage((10 +(v*10)), MaxY -20, VP_M, AND_PUT);
		putimage((10 +(v*10)), MaxY -20, VP, OR_PUT);
	}
}

//DESENHA VIDA DA TERRA
int DesenhaVidaT()
{
	for(t = 0; t < VidaTerra; t++)
	{
	
		putimage((750 +(t*10)), MaxY -20, VT_M, AND_PUT);
		putimage((750 +(t*10)), MaxY -20, VT, OR_PUT);
	}
	
}

// RESPAWN DOS JOGADORES
int Respawn()
{
	for(i = 0; i < 2; i++)
	{
		if(Player[i].situacao == 0 && timerRespawn > tRespawn) 
		{
			Player[i].situacao = 1;
		}
	}
}

// CONTROLE DO FINAL DE JOGO
int GameOver()
{
	if(VidaPlayer == 0) CenaGameOver();
	else if(VidaTerra == 0) CenaGameOver();
	else if(Boss[0].vida == 0) 
	{
		delay(2000);
		CenaFinal();
	}
	
}

//CENAS INICIAIS
int Cena1()
{
	putimage(0, 0, C1, COPY_PUT);
	outtextxy(0, 600, (char *)"O mundo inteiro estava em conflito.");
	outtextxy(0, 630, (char *)"Cegos pelo egoísmo e pela vontade de derrotar uns aos outros,");
	outtextxy(0, 660, (char *)"os países não tinham ideia do que estava se aproximando.");
	
	delay(7000);

	putimage(0, 0, C2, COPY_PUT);
	outtextxy(0, 610, (char *)"Entendendo a gravidade da situação, o cessar-fogo geral"); 
	outtextxy(0, 640, (char *)"fora anunciado. Os países se uniram para conter a");
	outtextxy(0, 670, (char *)"invasão alienígena e para salvar a Terra.");
	delay(4000);
	
	settextstyle(0, 0, 1);
	outtextxy(550, 680, (char *)"Pressione qualquer tecla para continuar.");
	getch();
	delay(1000);
}

//CENA FINAL
int CenaFinal()
{
	int pg = 2;

	settextstyle(0, 0, 2);
	setcolor(15);
	setfillstyle(0, 15);	
	while(status = 2)
	{
		if(pg == 2) pg = 1; else pg = 2;
		setactivepage(pg);
		cleardevice();
		
		putimage(0, 0, Final, COPY_PUT);
		outtextxy(0, 600, (char *)"Após a vitória da raça humana sobre os alienígenas,");
		outtextxy(0, 620, (char *)"os países perceberam a força que eles possuíam unidos.");
		outtextxy(0, 640, (char *)"E,então,a guerra teve seu fim.");
		outtextxy(0, 660, (char *)"O mundo finalmente estava em Paz!");
		
		setvisualpage(pg);
		
		if(GetKeyState(VK_ESCAPE)&0x80) status = 0;		
	}
}

//CENA DE DERROTA
int CenaGameOver()
{
	int pg = 2;
	while(status == 3)
	{
		if(pg == 2) pg = 1; else pg =1;
		setactivepage(pg);
		cleardevice();
		 
		DesenhaFundo();
		putimage(0, 0, GM, AND_PUT);
		putimage(0, 0, G, OR_PUT);
		
		setvisualpage(pg);
		
		getch();
		if(GetKeyState(VK_ESCAPE)&0x80) status = 1;
	}
}

// FUNÃ‡ÃƒO PRINCIPAL DO JOGO
int Jogo()
{
	int pg = 2; 
	char tecla = 0;
	
	settextstyle(0, 0, 2);
	setcolor(15);
	setfillstyle(1, 15);
	
	Cena1();
	
	while(status == 1)
	{
		if(pg == 2) pg = 1; else pg = 2;
		setactivepage(pg);
		cleardevice();
		
		timer1++;
		timer2++;
		timerRespawn++;
		
		for(i = 0; i < 10; i++) if(Tiro1[i].y < -30) Tiro1[i].situacao = 0;
		for(i = 0; i < 10; i++) if(Tiro2[i].y < -30) Tiro2[i].situacao = 0;
		for(i = 0; i < MaxInimigos; i++) if(Inimigos[i].y > MaxY) 
		{
			Inimigos[i].y = -100;
			Inimigos[i].passo = 0;
			Inimigos[i].situacao = 0;
			VidaTerra--;
			contInimigos++;	 
		}
		if(contInimigos >= 67) contInimigos = MaxInimigos;
		
		DesenhaFundo();
		DesenhaVidaP();
		DesenhaVidaT();
		DesenhaPlayer1();
		DesenhaPlayer2();
		InicializaInimigos();
		
		
		Chefao();			
		
		setvisualpage(pg);
		
		MovePlayer1();
		MovePlayer2();	
	
   		ExecutaTiro();
   		MoveTiro();
		

					
		if(GetKeyState(VK_ESCAPE)&0x80) status = 0;
		delay(30);

		colisaoTiro();
		colisaoBossTiro();
		colisaoJog1();
		Respawn();
		GameOver();
		
	} 

}

