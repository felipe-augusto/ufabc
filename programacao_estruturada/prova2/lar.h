typedef struct lar_s lar;

/*cria um lar*/
lar *cria_lar(char *tipo, char *cor, int area);

/*muda a cor de um lar*/
void muda_cor(lar *l, char *cor);

/*muda a area de um lar*/
void muda_area(lar *l, int area);

/*muda o tipo area de um lar*/
void muda_tipo(lar *l, char *tipo);

/*recebe o tipo de l*/
char* get_tipo(lar *l);

/*recebe a cor de l*/
char* get_cor(lar *l);

/*recebe a area de l*/
int get_area(lar *l);

/*imprime info do lar*/
void imprime(lar *l);


