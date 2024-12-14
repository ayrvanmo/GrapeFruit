/**
 * @User Users.c
 * @author Pendiente
 * @brief Funciones para manejo de usuarios
*/
#include "user.h"


UserList get_users_from_directory(char *directory, UserList list)
{
	DIR *dir;
	struct dirent *entry;
	dir = opendir(directory);
	if (dir == NULL)
	{
		print_error(305, directory, NULL);
		return NULL;
	}

	if(list == NULL){
		list = make_empty_userList(list);
	}
	// En este ciclo se revisa el contenido del directorio
	while((entry = readdir(dir)) != NULL){
		// En caso de que sea el identificador del directorio o su directorio raiz, se omite
		if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
			continue;
		}
		// En caso de que sea un directorio, se entra en este
		if(entry->d_type == 4 ){
			size_t length = strlen(directory) + strlen(entry->d_name) + 2;
			char *subDir = malloc(length);
			if(subDir == NULL){
				closedir(dir);
				print_error(200, NULL, NULL);
			}
			snprintf(subDir, length, "%s/%s/", directory, entry->d_name);

			// Se contruye la ruta de la info del usuario
			size_t infoLength = strlen(subDir) + strlen("info.txt") + 2;
			char *infoPath = malloc(infoLength);
			if(infoPath == NULL){
				closedir(dir);
				print_error(200, NULL, NULL);
			}
			snprintf(infoPath, infoLength, "%s/info.txt", subDir);

			// Se abre y rpocesa el archivo
			FILE *file = fopen(infoPath, "r");
			if(file == NULL){
				print_error(100, infoPath, NULL);
			}
			char description[MAX_DESCRIPTION];
			char line[256];
			int age;

			// Leer la primera línea y analizarla
			if (fgets(line, sizeof(line), file) != NULL) {
				sscanf(line, "%d", &age);
			}
			// Leer la segunda línea y analizarla
			if (fgets(line, sizeof(line), file) != NULL) {
				sscanf(line, "%[^\n]", description);
				//printf("Se ha leido la descripcion de %s :  %s\n",name, description);
			}
			fclose(file);
			insert_userList_user(list, list, entry->d_name, description, age);
			printf("Usuario %s insertado en lista de usuarios\n", entry->d_name);
			//printf("insertando usuario %s\n con descripcion: %s\n", name,description);
			free(subDir);
			free(infoPath);


		}
	}
	printf("Usuarios cargados\n");
	closedir(dir);
	return list;
}

Graph get_conections_from_directory(char *directory, UserList list, Graph graph)
{
	DIR *dir;
	struct dirent *entry;
	dir = opendir(directory);
	if (dir == NULL)
	{
		print_error(305, directory, NULL);
		return NULL;
	}

	if(graph == NULL){
		graph = create_graph(graph);
	}

	//Primer usuario de la lista e usuarios
	UserPosition P = list->Next;
	// Se van insertando los usuarios al grafo
	while(P != NULL){
		GraphPosition graphNode = insert_graphNode(P, graph);
		if(graphNode == NULL){
			print_error(200, NULL, NULL);
		}
		printf("Usuario %s insertado en el grafo\n", P->name);
		P = P->Next;
	}
	//print_graph(graph);

	// En este ciclo se revisa el contenido del directorio
	while((entry = readdir(dir)) != NULL){
		// En caso de que sea el identificador del directorio o su directorio raiz, se omite
		if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
			continue;
		}
		// En caso de que sea un directorio, se entra en este
		if(entry->d_type == 4 ){

			size_t length = strlen(directory) + strlen(entry->d_name) + 2;
			char *subDir = malloc(length);
			if(subDir == NULL){
				print_error(200, NULL, NULL);
			}
			snprintf(subDir, length, "%s/%s/", directory, entry->d_name);

			// Se contruye la ruta de los seguidos del usuario
			size_t followsLength = strlen(subDir) + strlen("follows.txt") + 2;
			char *followsPath = malloc(followsLength);
			if(followsPath == NULL){
				print_error(200, NULL, NULL);
			}
			snprintf(followsPath, followsLength, "%s/follows.txt", subDir);

			// Se abre y rpocesa el archivo
			FILE *file = fopen(followsPath, "r");
			if(file == NULL){
				print_error(100, followsPath, NULL);
			}

			char followedName[MAX_NAME];
			char line[256];

			GraphPosition userNode = find_graphNode(entry->d_name, graph);

			// Leer cada linea del archivo y procesar las conexiones
			while (fgets(line, sizeof(line), file) != NULL) {
				sscanf(line, "%s", followedName);
				UserPosition followedUser = find_userList_user(list, followedName);
				if (followedUser == NULL) {
					printf("Usuario %s no encontrado\n", followedName);
					continue;
				}
				GraphPosition followedNode = find_graphNode(followedName, graph);
				create_graph_edge(userNode, followedNode);
			}
			fclose(file);
			free(followsPath);


			// Se construye la ruta de los mutuals
			size_t mutualsLength = strlen(subDir) + strlen("mutuals.txt") + 2;
			char *mutualsPath = malloc(mutualsLength);
			if(mutualsPath == NULL){
				print_error(200, NULL, NULL);
			}
			snprintf(mutualsPath, mutualsLength, "%s/mutuals.txt", subDir);

			// Se abre y procesa el archivo
			file = fopen(mutualsPath, "r");
			if(file == NULL){
				print_error(100, mutualsPath, NULL);
			}
			while (fgets(line, sizeof(line), file) != NULL) {
        		sscanf(line, "%s", followedName);
        		GraphPosition followedNode = find_graphNode(followedName, graph);
				if(followedNode == NULL){
					printf("Usuario %s no encontrado\n", followedName);
					continue;
				}
            	//printf("Usuario %s y usuario %s son mutuals\n", userNode->user->name, followedNode->user->name);
            	userNode->user->mutuals->next = insert_friendList_node(userNode->user->mutuals, followedNode);
            	userNode->user->friendCount++;
    		}

			free(mutualsPath);
			free(subDir);
			fclose(file);
		}
	}

	printf("Conexiones cargadas\n");


	closedir(dir);
	return graph;

}

Graph get_preferences_from_directory(char *directory, UserList list, Graph graph)
{
	DIR *dir;
	struct dirent *entry;
	dir = opendir(directory);
	if (dir == NULL)
	{
		print_error(305, directory, NULL);
		return NULL;
	}
	printf("Cargando preferencias\n");

	// En este ciclo se revisa el contenido del directorio
	while((entry = readdir(dir)) != NULL){
		// En caso de que sea el identificador del directorio o su directorio raiz, se omite
		if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
			continue;
		}
		// En caso de que sea un directorio, se entra en este
		if(entry->d_type == 4 ){

			size_t length = strlen(directory) + strlen(entry->d_name) + 2;
			char *subDir = malloc(length);
			if(subDir == NULL){
				print_error(200, NULL, NULL);
			}
			snprintf(subDir, length, "%s/%s/", directory, entry->d_name);

			// Se contruye la ruta de las preferencias del usuario
			size_t preferencesLength = strlen(subDir) + strlen("preferences.txt") + 2;
			char *preferencesPath = malloc(preferencesLength);
			if(preferencesPath == NULL){
				print_error(200, NULL, NULL);
			}
			snprintf(preferencesPath, preferencesLength, "%s/preferences.txt", subDir);
			//printf("Ruta de preferencias: %s\n", preferencesPath);
			// Se abre y procesa el archivo
			FILE *file = fopen(preferencesPath, "r");
			if(file == NULL){
				print_error(100, preferencesPath, NULL);
			}

			char preference[MAX_NAME];
			char line[256];
			printf("Usuario %s\n", entry->d_name);
			UserPosition user = find_userList_user(list, entry->d_name);
			///printf("Usuario %s\n", user->name);
			if(user == NULL){
				printf("Usuario %s no encontrado\n", entry->d_name);
				continue;
			}

			// Leer cada linea del archivo y procesar las preferencias
			while (fgets(line, sizeof(line), file) != NULL) {
				sscanf(line, "%s", preference);
				printf("Usuario %s tiene preferencia %s\n", user->name, preference);
				insert_interestNode(preference, user->interests);
			}
			fclose(file);
			free(preferencesPath);
			free(subDir);
		}
	}

	printf("Preferencias cargadas\n");
	closedir(dir);
	return graph;
}


void fill_array_with_interests_from_file(char array[MAX_INTERESTS][MAX_INTEREST_NAME])
{
    char *preferencesData = "data/interest/interest.txt";
    FILE *file = fopen(preferencesData, "r");
    if (file == NULL) {
        print_error(100, preferencesData, NULL);
        return;
    }
    int i = 0;
    while (i < MAX_INTERESTS && fgets(array[i], MAX_INTEREST_NAME, file) != NULL) {
        array[i][strcspn(array[i], "\n")] = '\0'; // Quitar el salto de linea
        i++;
    }
    fclose(file);
}

void fill_array_with_names_from_file(char array[MAX_STOCK_NAMES][MAX_NAME])
{
    char *namesData = "data/names/names.txt";
    FILE *file = fopen(namesData, "r");
    if (file == NULL) {
        print_error(100, namesData, NULL);
        return;
    }
    int i = 0;
    while (i < MAX_STOCK_NAMES && fgets(array[i], MAX_NAME, file) != NULL) {
        array[i][strcspn(array[i], "\n")] = '\0'; // Quitar el salto de linea
        i++;
    }
    fclose(file);
}

/**
 * @brief Inserta un user en la lista de usuarios
 * @param L Lista en la que se desea insertar el usuario
 * @param Prev Nodo previo al que se desea insertar el usuario
 * @param UserPath Ruta del usuario
 * @param name Nombre del usuario
 * @param id Identificador del usuario
 * @return Puntero al usuario creado
*/
UserPosition insert_userList_user(UserList L, UserPosition Prev, char* name, char* description, int age)
{
	UserPosition TmpCell;
	TmpCell = malloc(sizeof(struct _UserNode));

	if (TmpCell == NULL){
		print_error(200,NULL,NULL);
		return NULL;
	}
	TmpCell->name = malloc(strlen(name) + 1);
	if (TmpCell->name == NULL) {
		print_error(200, NULL, NULL);
	}
	strcpy(TmpCell->name, name);

	TmpCell->description = malloc(strlen(description) + 1);
	if (TmpCell->description == NULL) {
		print_error(200, NULL, NULL);
	}
	strcpy(TmpCell->description, description);

	TmpCell->age = age;
	TmpCell->Next = Prev->Next;
	TmpCell->friendCount = 0;
	TmpCell->mutuals = create_empty_friendList(NULL);
	TmpCell->preferencesCount = 0;
	TmpCell->posts = create_empty_preferencesList(NULL);
	TmpCell->interests = init_interestTable();
	Prev->Next = TmpCell;
	L->friendCount++;
	return TmpCell;
}

/**
 * @brief imprime la lista de usuarios
 * @param L Lista de usuarios
 */
void print_userList(UserList L)
{
	printf("Numero de usuarios: %d\n", L->friendCount);
	UserPosition P = L->Next;
	printf("Lista de usuarios:\n");

	while (P != NULL) {
		printf(", Nombre: %s, Edad: %d , Cantidad de mutuals: %d , Mutuals: ", P->name, P->age, P->friendCount);
		print_friendList(P->mutuals);
		printf(", Interests: ");
		print_interestTable(P->interests);
		printf("descripcion: %s \n", P->description);
		printf("Publicaciones: ");
		print_preferencesList(P->posts);
		printf("\n");
		P = P->Next;
		//printf("leido bien\n");
	}

}

/**
 * @brief Elimina la lista de usuarios
 * @param L Lista de usuarios
 */
void delete_userList(UserList L)
{
	UserPosition P = L->Next;

	while (P != NULL) {
		delete_userList_user(L, P);
		P = L->Next;
	}
	free(L);
}

/**
 * @brief Crea una lista de usuarios vacia
 * @param L Lista de usuarios
 * @return Lista de usuarios vacia
 */
UserList make_empty_userList(UserList L)
{
	if (L != NULL){
		delete_userList(L);
	}
	L = malloc(sizeof(struct _UserNode));
	if (L == NULL) {
		print_error(200,NULL,NULL);
	}
	L->Next = NULL;
	L->friendCount = 0;
	return L;
}

/**
 * @brief Cuenta el numero de usuarios en la lista de usuarios
 * @param L Lista de usuarios
 * @return Numero de usuarios
 */
int count_usersList(UserList L)
{
	return L->friendCount;
}

/**
 * @brief Elimina un usuario de la lista de usuarios
 * @param L Lista de usuarios
 * @param UserName Nombre del usuario a eliminar
 */
void delete_userList_user(UserList L, UserPosition user)
{
	if(user == NULL){
		print_error(203, NULL, NULL);
	}
	UserPosition prevNode = find_userList_prev_user(L, user);
	if(prevNode == NULL){
		print_error(301, NULL, NULL);
		return;
	}

	delete_friendList(user->mutuals);
	delete_interestTable(user->interests);
	delete_preferencesList(user->posts);
	prevNode->Next = user->Next;
	free(user->name);
	free(user->description);
	free(user);
}

/**
 * @brief Encuentra un usuario en la lista de usuarios
 * @param L Lista de usuarios
 * @param UserName Nombre del usuario a buscar
 */
UserPosition find_userList_user(UserList L, char* userName)
{
	UserPosition P = L->Next;
	while (P != NULL && strcmp(P->name, userName) != 0) {
		P = P->Next;
	}
	return P;
}

/**
 * @brief Encontrar el usuario anterior a @p user en @p L
 * @param L Lista de usuarios
 * @param User Puntero a la estructura que contiene información sobre el usuario
 * @return Puntero a la estructura que contiene información sobre el usuario
*/
UserPosition find_userList_prev_user(UserList L, UserPosition user)
{
	UserPosition aux = L;
	while (aux != NULL && aux->Next != user){
		aux = aux->Next;
	}
	return aux;
}

void make_recomendations_for_user(UserPosition user, UserList list, Graph graph)
{
	UserPosition P = list->Next;
	while(P != NULL){
		if(P == user){
			P = P->Next;
			continue;
		}
		double jaccard = calculate_jaccard(user, P);
		GraphPosition userNode = find_graphNode(user->name, graph);
		GraphPosition PNode = find_graphNode(P->name, graph);
		if(find_friendList_node(userNode->follows, PNode) != NULL){
			P= P->Next;
			continue;
		}
		if(coin_toss(jaccard) == true ){
			create_graph_edge(userNode, PNode);
			if(find_friendList_node(PNode->follows, userNode) != NULL ){
				printf("Usuario %s y usuario %s son mutuals\n", user->name, P->name);
				user->mutuals->next = insert_friendList_node(user->mutuals, PNode);
				user->friendCount++;
				P->mutuals->next = insert_friendList_node(P->mutuals, userNode);
				P->friendCount++;
			}
		}
		//ACTIVAR DESPUES 
		//save_connections_in_files(graph, user);
		//printf("Jaccard entre %s y %s: %f\n", user->name, P->name, jaccard);
		P = P->Next;
	}
}

void create_users_batch(UserList list, Graph graph, char interests[MAX_INTERESTS][MAX_INTEREST_NAME], char names[MAX_STOCK_NAMES][MAX_NAME])
{
	int floor = list->friendCount;
	int limit = list->friendCount + profiles_per_tick(list->friendCount);

	for(int i = floor; i < limit; i++){
		char name[MAX_NAME];
		char temp_name[MAX_NAME];
		strcpy(temp_name, names[rand() % MAX_STOCK_NAMES]);
		strcpy(name, temp_name);
		int age = rand() % 60 + 18;
		while(find_userList_user(list, name) != NULL){
			snprintf(name, MAX_NAME, "%s%d", temp_name, rand() % 100 + 1);
			//printf("Nombre repetido, cambiando a %s\n", name);
		}
		UserPosition P = insert_userList_user(list, list, name, "Soy un usuario creado! Gracias por ver mi perfil", age);

		for(int j = 0; j < 9; j++){
			insert_interestNode(interests[rand() % MAX_INTERESTS], P->interests);
		}

		// ACTIVAR DESPUESSS
		//create_user_folder("data/users/", P);

		//GUARDAR ESTOS DATOS EN EL ARCHIVO DE USUARIOS
		insert_graphNode(P, graph);
	}
}
// WARNING, TENER CUIDADO CON EL PERMISO OTORGADO
void create_user_folder(char *directory, UserPosition user)
{
	char *userDir = malloc(strlen(directory) + strlen(user->name) + 2);
	if(userDir == NULL){
		print_error(200, NULL, NULL);
	}

	snprintf(userDir, strlen(directory) + strlen(user->name) + 2, "%s/%s/", directory, user->name);
	printf("Directorio de usuario: %s\n", userDir);
	if(mkdir(userDir, 0755) == -1){
		print_error(200, NULL, NULL);
	}
	char *infoPath = malloc(strlen(userDir) + strlen("info.txt") + 2);
	if(infoPath == NULL){
		print_error(200, NULL, NULL);
	}
	snprintf(infoPath, strlen(userDir) + strlen("info.txt") + 2, "%s/info.txt", userDir);
	FILE *file = fopen(infoPath, "w");
	if(file == NULL){
		print_error(100, infoPath, NULL);
	}
	fprintf(file, "%d\n", user->age);
	fprintf(file, "%s\n", user->description);
	fclose(file);
	free(infoPath);

	char *followsPath = malloc(strlen(userDir) + strlen("follows.txt") + 2);
	if(followsPath == NULL){
		print_error(200, NULL, NULL);
	}
	snprintf(followsPath, strlen(userDir) + strlen("follows.txt") + 2, "%s/follows.txt", userDir);
	file = fopen(followsPath, "w");
	if(file == NULL){
		print_error(100, followsPath, NULL);
	}
	fclose(file);
	free(followsPath);

	char *mutualsPath = malloc(strlen(userDir) + strlen("mutuals.txt") + 2);
	if(mutualsPath == NULL){
		print_error(200, NULL, NULL);
	}
	snprintf(mutualsPath, strlen(userDir) + strlen("mutuals.txt") + 2, "%s/mutuals.txt", userDir);
	file = fopen(mutualsPath, "w");
	if(file == NULL){
		print_error(100, mutualsPath, NULL);
	}
	fclose(file);
	free(mutualsPath);

	char *preferencesPath = malloc(strlen(userDir) + strlen("preferences.txt") + 2);
	if(preferencesPath == NULL){
		print_error(200, NULL, NULL);
	}
	snprintf(preferencesPath, strlen(userDir) + strlen("preferences.txt") + 2, "%s/preferences.txt", userDir);
	file = fopen(preferencesPath, "w");
	if(file == NULL){
		print_error(100, preferencesPath, NULL);
	}

	printf("porsiaca\n");
	for(int i = 0; i < INTEREST_TABLE_SIZE; i++){
		InterestPosition P = user->interests[i].interestList;
		if(P->next != NULL){
			P = P->next;
		}
		while(P->key != NULL){
			fprintf(file, "%s\n", P->key);
			P = P->next;
			if(P == NULL){
				break;
			}
		}
	}

	fclose(file);
	free(preferencesPath);
	free(userDir);

	// ANHADIR EL APARTADO DE LAS PUBLICACIONES


}

void save_connections_in_files(Graph graph, UserPosition user)
{
	GraphPosition userNode = find_graphNode(user->name, graph);
	char *userDir = malloc(strlen("data/users/") + strlen(user->name) + 2);
	if(userDir == NULL){
		print_error(200, NULL, NULL);
	}
	snprintf(userDir, strlen("data/users/") + strlen(user->name) + 2, "data/users/%s/", user->name);

	char *followsPath = malloc(strlen(userDir) + strlen("follows.txt") + 2);
	if(followsPath == NULL){
		print_error(200, NULL, NULL);
	}
	snprintf(followsPath, strlen(userDir) + strlen("follows.txt") + 2, "%s/follows.txt", userDir);
	FILE *file = fopen(followsPath, "w");
	if(file == NULL){
		print_error(100, followsPath, NULL);
	}
	FriendPosition P = userNode->follows->next;

	while(P != NULL){
		fprintf(file, "%s\n", P->graphNode->user->name);
		P = P->next;
	}
	fclose(file);
	free(followsPath);

	char *mutualsPath = malloc(strlen(userDir) + strlen("mutuals.txt") + 2);
	if(mutualsPath == NULL){
		print_error(200, NULL, NULL);
	}
	snprintf(mutualsPath, strlen(userDir) + strlen("mutuals.txt") + 2, "%s/mutuals.txt", userDir);
	file = fopen(mutualsPath, "w");
	if(file == NULL){
		print_error(100, mutualsPath, NULL);
	}
	FriendPosition Q = user->mutuals->next;
	while(Q != NULL){
		fprintf(file, "%s\n", Q->graphNode->user->name);
		Q = Q->next;
	}
	fclose(file);
	free(mutualsPath);
	free(userDir);
}