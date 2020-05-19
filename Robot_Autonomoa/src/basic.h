#ifndef SRC_BASIC_H_
#define SRC_BASIC_H_

	#define PANTAILA_ALTUERA 720
	#define PANTAILA_ZABALERA 1280

	int LeihoaEtaRenderHasi();		//Lehia eta rendera hasieratzen du, eta leihoari ikono bat ematen dio, errorerik baldin badaude 1 bueltatuko du
	void PertsonaiaHasieratu();		//Jokatu sakatzean lehenengo aldiz pertsonaia kargatzera deitzen du
	void EtsaiakHasieratu();
	void GuztiakHil();
	void PertsonaiaHil();
	void EtsaiaKendu(int pos, int BizirikDaudenEtsaiak[], int BizirikKopurua);
	void RectEraikitzailea(SDL_Rect* dest, int x, int y, int h, int w);
	void BerrizJaurti();


#endif /* SRC_BASIC_H_ */
