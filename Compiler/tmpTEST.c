int f() {
	int z = 4;

	switch(z) {
		case 1: return 9;
		case 3 : break;
		case 4: z = z +1;

		case 5: return z;;
		default: return 0;
	}
}