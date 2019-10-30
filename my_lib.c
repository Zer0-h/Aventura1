// Antonio Torres Escribano DNI:45694675T

#include "my_lib.h"

size_t my_strlen(const char *str) {
  int len_counter = 0; // Contador de longitud de l'string
  while (*str++) { // Bucle on comprovem si el valor de str és 0 per sortir, és
    // a dir, el caràcter de la nostra posició es \0 i a més ens
    // movem una posició de str dins la comprobació. Mentres
    // estiguem en es bucle per cada caràcter que no és nul sumam
    // 1 al contador 'len_counter'.
    len_counter++;
  }
  return len_counter;
}

int my_strcmp(const char *str1, const char *str2) {
  int comp_res = 0; // Comprobació del resultat, contendrà la diferència dels
  // valors ASCII dels caràcters, si és 0, és que són iguals i
  // per tant hem de comprobar el següent caràcter dels dos
  // strings
  while (comp_res == 0 &&
         (*str1 || *str2)) { // Bucle on comprovem que la diferencia entre els
    // caràcters sigui igual i que a més no estiguem al
    // final de cap dels dos strings
    comp_res = (int)*str1 - (int)*str2; // Els passam a enters per obtenir el
                                        // seu valor de la taula ASCII
    str1++, str2++;
  }
  return comp_res;
}

char *my_strcpy(char *dest, const char *src) {
  int len = my_strlen(src) + 1; // Obtenim la longitud de l'string source més 1
                                // per incloure el caràcter nul (útil per es
                                // bucle for)
  for (int i = 0; i < len;
       i++) { // Afegim caràcter per caràcter d'src a dest inclòs el caràcter
              // nul fins, len ens indica quan acabam
    dest[i] = src[i];
  }
  return dest;
}

char *my_strncpy(char *dest, const char *src, size_t n) {
  for (int i = 0; i < n;
       i++) { // Igual que my_strcpy però l'usuari decidex n caràcters a copiar,
              // dest no inclou '\0' si n<len(src)
    dest[i] = src[i];
  }
  return dest;
}

char *my_strcat(char *dest, const char *src) {
  int len = my_strlen(dest);         // Longitud de l'string dest
  dest = my_strcpy(dest + len, src); // Movem el punter al final de la longitud
                                     // de l'string dest i copiam src a partir
                                     // de la nova posició de dest
  return dest - len; // Restam 'len' per tornar a la posició original de dest i
                     // així retornar un dest que és l'original més la cadena
                     // src
}

// Per test2.c

struct my_stack *my_stack_init(int size) {
  struct my_stack *tope; // Cream l'estructura tope perquè contengui el punter
                         // first (apuntant sempre al element més alt de la
                         // pila)
  tope = malloc(
      sizeof(struct my_stack)); // Assignam un espai de memòria a l'estructura
  tope->first = NULL; // Inicialment apuntarà a NULL, ja que no hi ha nodes
  tope->size = size; // Assignam el valor de size, que es el tamany de les dades
  return tope;
}
int my_stack_push(struct my_stack *stack, void *data) {
  struct my_stack_node *nuevo; // Cream un nou punter a una estructura on
                               // assignarem un espai de memoria per al nou node
                               // de la pila
  nuevo = malloc(sizeof(struct my_stack_node));
  if (stack == NULL || stack->size <= 0 ||
      nuevo == NULL) { // Comprovem que s'inicialitzi bé la pila i que hi hagi
                       // memòria suficient (nuevo != NULL), si no, tornarem un
                       // error
    return -1;
  } else {
    nuevo->data = data; // Assignam el punter data al valor donat per la funció
    nuevo->next = stack->first; // Assignam el punter next al que estaba
                                // senyalat anteriorment per first
    stack->first = nuevo; // El punter first apuntarà a la nova estructura
    return 0;
  }
}

void *my_stack_pop(struct my_stack *stack) {
  if (stack->first ==
      NULL) { // Comprovam que hi hagi al menys un node per continuar
    return NULL;
  }
  void *to_free =
      stack->first; // Guardam un punter amb la posició del primer node
  void *to_return =
      stack->first->data; // Guardam el punter de data per tornarlo més tard
  stack->first = stack->first->next; // Canviam el punter al primer node de la
                                     // pila abans d'eliminar s'anterior
  free(to_free);                     // Eliminam el nodo però no les dades
  return to_return;
}

int my_stack_len(struct my_stack *stack) {
  if (stack->first == NULL) { // Si no hi ha nodes, tornarem 0
    return 0;
  }
  struct my_stack_node *tmp_node = stack->first;
  int counter = 1;         // Contendrá el número d'elements en la pila
  while (tmp_node->next) { // Mentres el punter al següent node no sigui NULL
                           //  no haurem acabat de recorrer la pila
    counter++;
    tmp_node = tmp_node->next; // Assignam el següent node per comprovar
  }
  return counter;
}

int my_stack_purge(struct my_stack *stack) {
  int bytes_counter = sizeof(struct my_stack); // Contam primer el tamany de
                                               // l'estructura stack, que sirà
                                               // la darrera que eliminarem
  while (stack->first) { // Bucle mentres encara hi hagi nodes
    bytes_counter += sizeof(struct my_stack_node) +
                     stack->size; // Li sumam el tamany del node i el de les
                                  // dades, que eliminarem a continuació
    free(my_stack_pop(stack)); // my_stack_pop ens torna la posició de les dades
                               // que eliminam, en el proces eliminam el node
  }
  free(stack); // Lliberam l'estructura stack i tornam els bytes de tota la pila
  return bytes_counter;
}

int my_stack_write(struct my_stack *stack, char *filename) {
  // Cream una pila auxiliar invertint l'ordre dels nodes per després
  // escriurer-ho en un arxiu
  struct my_stack *tope = my_stack_init(stack->size);
  struct my_stack_node *tmp_node = stack->first; // Estructura temporal per
                                                 // recorrer la pila original en
                                                 // un bucle
  while (tmp_node->next) {
    my_stack_push(tope, tmp_node->data); // Guardam el node a la nova pila
    tmp_node = tmp_node->next;           // i passam al següent
  }
  my_stack_push(tope, tmp_node->data); // Com el darrer node és ignorat dins el
                                       // while ho feim fora

  int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if (fd < 0) // Comprovem que s'hagi executat bé el comand open()
    return -1;
  int ele_counter = 0; // Variable a tornar, numero d'elements que hem escrit
  write(fd, &(tope->size), sizeof(int)); // Escribim el tamany de les dades
                                         // primer per després saber com tornar
                                         // a montar la pila llegint s'arxiu
  while (tope->first) {
    write(fd, my_stack_pop(tope), tope->size); // Mentres escribim a l'arxiu
                                               // eliminam els nodes temporals i
                                               // sumam 1 als elements escrits
    ele_counter++;
  }
  free(tope); // Finalment lliberam es tope temporal i tancam s'arxiu
  fd = close(fd);
  return ele_counter;
}

struct my_stack *my_stack_read(char *filename) {
  void *data; // Cream un punter per a les dades
  int fd = open(filename, O_RDONLY), size;
  if (fd < 0) { // Comprovem que s'hagi executat bé el comand open()
    return NULL;
  }
  read(fd, &size,
       sizeof(int)); // Llegim el tamany de les dades i inicialitzam la pila

  struct my_stack *tope = my_stack_init(size);

  for (data = malloc(tope->size); read(fd, data, tope->size);
       data = malloc(tope->size)) { // Mentres llegim dades cream espai per
                                    // elles, les escribim i les montam a sa pila
    my_stack_push(tope, data);
  }

  fd = close(fd); // Tancam l'arxiu i tornam el punter tope, que apunta a la pila
  return tope;
}