int aleat_num(int inf, int sup){
	float random;

	if(inf < 0 || sup < 0 || sup < inf){
		fprintf(stderr, "Error en la entrada de argumentos a aleat_num");
		return -1; /*ERROR*/
	}

	random = rand();
	random /= RAND_MAX;
	random *= (sup-inf+1);
	random += inf;
	if(random > sup){
		random = sup;
	}
	return (int)random;
}