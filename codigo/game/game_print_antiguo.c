void game_print_screen(Game* game){
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID; /* !< Ids for locations*/
  Id id_l_back = NO_ID, id_l_next = NO_ID; /*!< Ids of the links*/
  Space* space_act = NULL; /* !< Pointers to spaces needed to print the game*/
  Space* space_back = NULL;
  Space* space_next = NULL;
  char obj[WORD_SIZE]; /* !< String with the objects*/
  char aux[WORD_SIZE]; /* !< Axiliar for reading object values*/
  int i, last; /* !< loops, last rolled value*/
  int obj_size; /* !< Control of the number of objects to print*/

  obj[0] = '\0'; /* !< Set to empty*/
  
  id_act = game_get_player_location(game);

  if (id_act == NO_ID){
    return;
  }
  
  space_act = game_get_space(game, id_act);
  id_l_back = space_get_north(space_act);
  id_l_next = space_get_south(space_act);

  /*Search for the id of the back space*/
  for(i=0; i<(4*MAX_SPACES); i++){
    if(link_get_id(game->links[i]) == id_l_back){
      if(link_get_conection1(game->links[i]) == id_act){
        id_back = link_get_conection2(game->links[i]);
        break;
      }
      else{
        id_back = link_get_conection1(game->links[i]);
        break;
      }
    }
    else{
      id_back = NO_ID;
    }
  }

  /*Search for the id of the next space*/
  for(i=0; i<(4*MAX_SPACES); i++){
    if(link_get_id(game->links[i]) == id_l_next){
      if(link_get_conection1(game->links[i]) == id_act){
        id_next = link_get_conection2(game->links[i]);
        break;
      }
      else{
        id_next = link_get_conection1(game->links[i]);
        break;
      }
    }
    else{
      id_next = NO_ID;
    }
  }

  space_back = game_get_space(game, id_back);
  space_next = game_get_space(game, id_next);  
  
  if(system(CLEAR))
  	 return; 
  obj_size = 0;

  for(i = 0; i < game->num_objects; i++){
    if (object_get_location(game->object[i]) == id_back){
      aux[0] = object_get_symbol(game->object[i]);
      aux[1] = '\0';
      strcat(obj,aux); /*add the symbol*/
      obj_size++; 
    }
  }
  /*In case there are more than 3 objects*/
  if(obj_size > 3){
    obj[3] = '.';
    obj[4] = '.';
    obj[5] = '.';
    obj[6] = '\0';
  }

  if (id_back != NO_ID) {
    if(space_get_east(space_back) != NO_ID){
      for(i=0; i<(4*MAX_SPACES); i++){
        if(link_get_id(game->links[i]) == space_get_east(space_back)){
          if(link_get_conection1(game->links[i]) == id_back){
            printf("|         %2d| --> %d \n",(int) id_back, (int) link_get_conection2(game->links[i]));
            break;
          }
          else{
            printf("|         %2d| --> %d \n",(int) id_back, (int) link_get_conection1(game->links[i]));
            break;
          }
        }
      }
    }
    else{
      printf("|         %2d|\n",(int) id_back);
    }  
    printf("%s", space_get_gdesc(space_back));
    printf("|           |\n");
    printf("| %-6s    |\n",obj);
    printf("+-----------+\n");
    printf("      ^ %d\n", (int) id_l_back);
  }
  
  obj[0] = '\0'; /*Set to empty*/
  obj_size = 0;

  for(i = 0; i < game->num_objects; i++){
    if (object_get_location(game->object[i]) == id_act) {
      aux[0] = object_get_symbol(game->object[i]);
      aux[1] = '\0';
      strcat(obj,aux); /*add the symbol*/
      obj_size++;
    }
  }
  /*In case there are more than 3 objects*/
  if(obj_size > 3){
    obj[3] = '.';
    obj[4] = '.';
    obj[5] = '.';
    obj[6] = '\0';
  }

  if (id_act != NO_ID) {
    if(space_get_east(space_act) != NO_ID){
      printf("+-----------+ %d\n", (int) space_get_east(space_act));
      for(i=0; i<(4*MAX_SPACES); i++){
        if(link_get_id(game->links[i]) == space_get_east(space_act)){
          if(link_get_conection1(game->links[i]) == id_act){
            printf("| >8D     %2d| --> %d \n",(int) id_act, (int) link_get_conection2(game->links[i]));
            break;
          }
          else{
            printf("| >8D     %2d| --> %d \n",(int) id_act, (int) link_get_conection1(game->links[i]));
            break;
          }
        }
      }
    }
    else{
      printf("+-----------+\n");
      printf("| >8D     %2d|\n",(int) id_act);
    } 
    printf("%s", space_get_gdesc(space_act));
    printf("|           |\n");
    printf("| %-6s    |\n",obj);
    printf("+-----------+\n");
  }

  obj[0] = '\0'; /*Set to empty*/
  obj_size = 0;

   for(i = 0; i < game->num_objects; i++){
    if (object_get_location(game->object[i]) == id_next) {
      aux[0] = object_get_symbol(game->object[i]);
      aux[1] = '\0';
      strcat(obj,aux); /*add the symbol*/
      obj_size++;
    }
  }
  /*In case there are more than 3 objects*/
  if(obj_size > 3){
    obj[3] = '.';
    obj[4] = '.';
    obj[5] = '.';
    obj[6] = '\0';
  }
  
  if (id_next != NO_ID) {
    printf("      v %d\n", (int) id_l_next);
    if(space_get_east(space_next) != NO_ID){
      printf("+-----------+ %d\n", (int) space_get_east(space_next));
      for(i=0; i<(4*MAX_SPACES); i++){
        if(link_get_id(game->links[i]) == space_get_east(space_next)){
          if(link_get_conection1(game->links[i]) == id_next){
            printf("|         %2d| --> %d \n",(int) id_next, (int) link_get_conection2(game->links[i]));
            break;
          }
          else{
            printf("|         %2d| --> %d \n",(int) id_next, (int) link_get_conection1(game->links[i]));
            break;
          }
        }
      }
    }
    else{
      printf("+-----------+\n");
      printf("|         %2d|\n",(int) id_next);
    } 
    printf("%s", space_get_gdesc(space_next));
    printf("|           |\n");
    printf("|  %-6s   |\n",obj);
  }
  
  printf("Object locations:");
  for(i = 0; i < game->num_objects; i++){
    if(object_get_location(game->object[i]) != PLAYER_OBJ){
	    printf(" %c:%d", object_get_symbol(game->object[i]), (int)object_get_location(game->object[i]));
    }
  }    
  printf("\n");

  printf("Player objects: ");
  for(i=0; i< game->num_objects; i++){
	if(object_get_location(game->object[i]) == PLAYER_OBJ)
		printf("%c ", object_get_symbol(game->object[i]));
  }

  printf("\n");

    

  last = die_get_last_roll(game->die);
  if(last != -1){
    printf("Last die value: %d\n", last);
  }

  if(strlen(game->desc) != 0){
	printf("Description: %s\n", game->desc);
  }
  game->desc[0] = '\0';


  printf("\n[commands: quit or q, drop or d, pick or p, roll or r, inspect or i, go or g]");
  printf("\nprompt:> ");
}