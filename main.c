/* CODIGO ELABORADO POR MIGUEL GENARO RODRIGUEZ */

#include <stdlib.h>
#include <stdio.h>
#include <conio.c>
#include <conio.h>
#include <string.h>
#include <time.h>

#define CT YELLOW
#define CF BLUE
#define CTS BLUE
#define CFS YELLOW
#define CET BLACK
#define CEF MAGENTA

#define TFBG LIGHTGRAY
#define TFT BLUE

#define POSX 6
#define POSY 5

#define ARRIBA 72
#define ABAJO 80
#define DERECHA 77
#define IZQUIERDA 75
#define ESC 27
#define ENTER 13
#define BKSP 8
#define PUNTO '.'
#define ESP ' '

#define OPC 7
#define TAMAOPC 80
#define LENTITLE 35

#define FULLTEXT 0
#define LETTERS 1
#define NUMBERS 2
#define DATEF 3

#define NUMBERFIELDLEN 10

#define HIDECHAR 1
#define SHOWCHAR 0

#define ADD 0
#define EDIT 1

#define WARNINGSDELAY 1900

#define MAXIDCLIENTE 15
#define MAXIDPROP 15
#define LENDATE 11
#define MAXID 12
#define LENPRINOMBRE 20
#define LENSEGNOMBRE 15
#define LENPRIAPEL 15
#define LENSEGAPEL 15
#define LENDIR 50
#define LENDESC 50
#define LINELEN 80
#define MAXIDPROY 6
#define MAXIDEQUIPO 5
#define MAXIDDEVOLUCION 6
#define MAXIDCONT 5
#define MAXNUMFACT 10
#define MAXTIPOFACT 8

#define DYNAMICITEMSTOSHOW 6

#define PROPCLOSED 'C'
#define PROPINACTIVE 'I'
#define PROPACTIVE 'A'

#define CLIENTES_FILENAME "clientes.dat"
#define EQUIPOS_FILENAME "equipos.dat"
#define PROYECTOS_FILENAME "proyectos.dat"
#define PROPUESTAS_FILENAME "propcontratos.dat"
#define EQUIPROP_FILENAME "equiprops.dat"

typedef struct
{
   int dia, mes, agno;
} FECHA;

typedef struct FIELDPROP
{
   int type;
   int hideCharacters;
   int maxCharacters;
   int numberDecimals;
} FIELDPROP;

typedef struct
{
   char idcliente[MAXIDCLIENTE];
   char primernomb[LENPRINOMBRE];
   char segnomb[LENSEGNOMBRE];
   char primerapel[LENPRIAPEL];
   char segapel[LENSEGAPEL];
   char docid[MAXID];
   char direccion[LENDIR];
} CLIENTE;

typedef struct
{
   char idproyecto[MAXIDPROY];
   char descripcion[LENDESC];
   char idcliente[MAXIDCLIENTE];
} PROYECTO;

typedef struct
{
   char idpropcontrato[MAXIDPROP];
   char idproyecto[MAXIDPROY];
   FECHA fechapropcontrato;
   char status; // CERRADO: 0, INACTIVO: 1 y ACTIVO: 2
} PROPCONTRACTO;

typedef struct
{
   char idcliente[MAXIDCLIENTE];
   char idproyecto[MAXIDPROY];
   char idconteo[MAXIDCONT];
   char Descripcion[LENDESC];
   float monto;
} CUENTACLIENTE;

typedef struct
{
   char idequipo[MAXIDEQUIPO];
   char descripcion[LENDESC];
   int cantinventario;
   int cantprestados;
   float precioprestamo;
   float costoequipo;
} EQUIPO;

typedef struct
{
   char idpropcontrato[MAXIDPROP];
   char idequipo[MAXIDEQUIPO];
   int cantidad;
} EQUIPROP;

typedef struct
{
   char idpropcontrato[MAXIDPROP];
   char idconteo[MAXIDCONT];
   char idequipo[MAXIDEQUIPO];
   int cantidad;
   int cantdevuelta;
} CONTEO;

typedef struct
{
   char numfactura[MAXNUMFACT];
   char tipo[MAXTIPOFACT];
   char idpropcontrato[MAXIDPROP];
   char idconteo[MAXIDCONT];
   FECHA fecha;
   float monto;
} FACTURA;

typedef struct
{
   char iddevolucion[MAXIDDEVOLUCION];
   char idpropcontrato[MAXIDPROP];
   FECHA fecha;
} DEVOLUCION;

typedef struct
{
   char iddevolucion[MAXIDDEVOLUCION];
   char idpropcontrato[MAXIDPROP];
   char idconteo[MAXIDCONT];
   char idequipo[MAXIDEQUIPO];
   int cantidad;
   FECHA fecha;
} DETALLEDEVOLUCION;

//* NODOS DE CLIENTES
typedef struct nodo1
{
   CLIENTE cliente;
   struct nodo1 *sig;
   struct nodo1 *ant;
} NODOCLIENTE;

typedef struct
{
   NODOCLIENTE *start;
   NODOCLIENTE *end;
   int length;
} CLIENTLIST;

//* NODOS DE EQUIPOS
typedef struct nodo2
{
   EQUIPO equipo;
   struct nodo2 *sig;
   struct nodo2 *ant;
} NODOEQUIPO;

typedef struct
{
   NODOEQUIPO *start;
   NODOEQUIPO *end;
   int length;
} EQUIPOLIST;

//* NODOS DE PROYECTOS
typedef struct nodo3
{
   PROYECTO proyecto;
   struct nodo3 *sig;
   struct nodo3 *ant;
} NODOPROYECTO;

typedef struct
{
   NODOPROYECTO *start;
   NODOPROYECTO *end;
   int length;
} PROYECTOLIST;

//* NODO DE PROPUESTA DE CONTRATO
typedef struct nodo4
{
   PROPCONTRACTO propcontrato;
   struct nodo4 *sig;
   struct nodo4 *ant;
} NODOPROPCONTRACTO;

typedef struct
{
   NODOPROPCONTRACTO *start;
   NODOPROPCONTRACTO *end;
   int length;
} PROPCONTRACTOLIST;

//* NODO DE EQUIPOS EN PROPUESTA
typedef struct nodo5
{
   EQUIPROP equiprop;
   struct nodo5 *sig;
   struct nodo5 *ant;
} NODOEQUIPROP;

typedef struct
{
   NODOEQUIPROP *start;
   NODOEQUIPROP *end;
   int length;
} EQUIPROPLIST;

/* MANEJO DE MENUS */
void showOpcXY(char *, char **, int, int, int, int, int);
int movimiento(char *, char **, int, int, int, int, int);
char **toDynamicMenu(char[][TAMAOPC], int);
void freeDynamicMenu(char **, int);

/* MANEJO DE CAMPOS */
void showField(char *, FIELDPROP, int, int, int);
void capfieldAlpha(char *, int, int, FIELDPROP);
int isValidChar(FIELDPROP, char);
int dateValidation(int, int, int);
int validNumeric(FIELDPROP, char *, int px, int py);
int isEmptyField(char *, int, int);

/* SUBMENUS */
void showClientOptions(CLIENTLIST *);
void showProjectOptions(PROYECTOLIST *, CLIENTLIST *);
void showEquiposOptions(EQUIPOLIST *);
void showPropuestasOptions(PROPCONTRACTOLIST *, EQUIPROPLIST *, PROYECTOLIST *);

/* GUI: CLIENTES */
void showClientForm(CLIENTLIST *, int, int);
void showClientsMenu(CLIENTLIST *);
int showSelectedClientOptions(CLIENTLIST *, int);

/* GUI: EQUIPOS */
void showEquipoForm(EQUIPOLIST *, int, int);
void showEquiposMenu(EQUIPOLIST *);
int showSelectedEquipoOptions(EQUIPOLIST *, int);

/* GUI: PROYECTOS */
void showProyectoForm(PROYECTOLIST *, CLIENTLIST *, int, int);
void showProyectosMenu(PROYECTOLIST *);
int showSelectedProyectoOptions(PROYECTOLIST *, int);

/* GUI: PROPUESTAS DE CONTRATO */
void showPropuestasForm(PROPCONTRACTOLIST *, PROYECTOLIST *, int, char[MAXIDPROP]);
void showPropuestasMenu(PROPCONTRACTOLIST *, EQUIPROPLIST *equipropList, char);
int showSelectedPropuestasOptions(PROPCONTRACTOLIST *, EQUIPROPLIST *equipropList, char[MAXIDPROP]);

void showEquiPropForm(PROPCONTRACTOLIST *propuestaList, EQUIPROPLIST *equipropList, int mode, char idProp[MAXIDPROP], char idEquiProp[MAXIDEQUIPO]);

/* FUNCIONES: CLIENTES */
NODOCLIENTE *createClientNode(CLIENTE);
CLIENTLIST *createClientList();
void addClient(CLIENTLIST *, CLIENTE);
char **getClientsNames(CLIENTLIST *);
void deleteClientByPosition(CLIENTLIST *, int);
NODOCLIENTE *findClientById(NODOCLIENTE *, char[MAXIDCLIENTE]);
NODOCLIENTE *findClientByPosition(CLIENTLIST *, int);
void updateClientByPosition(CLIENTLIST *, CLIENTE, int);
void generateClientId(CLIENTLIST *, char[MAXIDCLIENTE]);
char *getLastClientId(CLIENTLIST *);
void freeClientListComplete(CLIENTLIST *);

/* FUNCIONES: EQUIPOS */
NODOEQUIPO *createEquipoNode(EQUIPO);
EQUIPOLIST *createEquipoList();
void addEquipo(EQUIPOLIST *, EQUIPO);
void deleteEquipoByPosition(EQUIPOLIST *, int);
void updateEquipoByPosition(EQUIPOLIST *, EQUIPO, int);
void generateEquipoId(EQUIPOLIST *, char[MAXIDEQUIPO]);
char *getLastEquipoId(EQUIPOLIST *);
char **getEquiposIDs(EQUIPOLIST *);
NODOEQUIPO *findEquipoByPosition(EQUIPOLIST *, int);
void freeEquipoListComplete(EQUIPOLIST *);

/* FUNCIONES: PROYECTOS */
NODOPROYECTO *createProyectoNode(PROYECTO);
PROYECTOLIST *createProyectoList();
void addProyecto(PROYECTOLIST *, PROYECTO);
void deleteProyectoByPosition(PROYECTOLIST *, int);
void updateProyectoByPosition(PROYECTOLIST *, PROYECTO, int);
void generateProyectoId(PROYECTOLIST *, char[MAXIDPROY]);
char *getLastProyectoId(PROYECTOLIST *);
char **getProyectosIDs(PROYECTOLIST *);
NODOPROYECTO *findProyectoByPosition(PROYECTOLIST *, int);
NODOPROYECTO *findProyectoById(PROYECTOLIST *, char[MAXIDPROY]);
void freeProyectoListComplete(PROYECTOLIST *);

/* FUNCIONES: PROPUESTA DE CONTRATO */
NODOPROPCONTRACTO *createPropContratoNode(PROPCONTRACTO);
PROPCONTRACTOLIST *createPropContratoList();
void addPropContrato(PROPCONTRACTOLIST *, PROPCONTRACTO);
void deletePropContrato(PROPCONTRACTOLIST *, char[MAXIDPROP]);
void updatePropContrato(PROPCONTRACTOLIST *list, PROPCONTRACTO propuesta);
void generatePropContratoId(PROPCONTRACTOLIST *, char[MAXIDPROP]);
char *getLastPropContratoId(PROPCONTRACTOLIST *);
char **getPropContratosIDsByStatus(PROPCONTRACTOLIST *, char);
NODOPROPCONTRACTO *findPropContratoById(PROPCONTRACTOLIST *, char[MAXIDPROP]);
void freePropContratoListComplete(PROPCONTRACTOLIST *);

/* FUNCIONES: EQUIPO EN PROPUESTA */
EQUIPROPLIST *createEquiPropList();
NODOEQUIPROP *createEquiPropNode(EQUIPROP);
char **getEquiposProp(PROPCONTRACTOLIST *, EQUIPROPLIST *, char idProp[MAXIDPROP]);
void addEquiProp(EQUIPROPLIST *, EQUIPROP);
void deleteEquiProp(PROPCONTRACTOLIST *, EQUIPROPLIST *, char idPro[MAXIDPROP], char idEquiProp[MAXIDEQUIPO]);
void freeEquiPropListComplete(EQUIPROPLIST *);

/* MANEJO DE ARCHIVOS */
void loadClientList(CLIENTLIST *);
void loadEquipoList(EQUIPOLIST *);
void loadProyectoList(PROYECTOLIST *);
void loadPropContratoList(PROPCONTRACTOLIST *);
void loadEquiPropList(EQUIPROPLIST *);

void saveClientListChanges(CLIENTLIST *);
void saveEquipoListChanges(EQUIPOLIST *);
void saveProyectoListChanges(PROYECTOLIST *);
void savePropContratoListChanges(PROPCONTRACTOLIST *);
void saveEquiPropListChanges(EQUIPROPLIST *);

/* AUXILIARES */
int showConfirmMenu(char *);
int isLeapYear(int);
int randrange(int, int);
void setColor(int, int);
void colorDefault();

int main()
{
   // INICIALIZAR LISTA DE CLIENTES
   CLIENTLIST *clientList = createClientList();
   loadClientList(clientList);

   // INICIALIZAR LISTA DE EQUIPOS
   EQUIPOLIST *equipoList = createEquipoList();
   loadEquipoList(equipoList);

   // INICIALIZAR LISTA DE PROYECTOS
   PROYECTOLIST *proyectoList = createProyectoList();
   loadProyectoList(proyectoList);

   // INICIALIZAR LISTA DE PROPUESTAS DE CONTRATO
   PROPCONTRACTOLIST *propContractList = createPropContratoList();
   loadPropContratoList(propContractList);

   // INICIALIZAR LISTA DE EQUIPOS EN PROPUSTAS
   EQUIPROPLIST *equiPropList = createEquiPropList();
   loadEquiPropList(equiPropList);

   // MENU PRINCIPAL
   char nom_create_menu[][TAMAOPC] = {
       "Clientes",
       "Equipos",
       "Proyectos",
       "Propuestas de Contrato",
       "Acceso",
       "<- Salir",
   };
   int qty = sizeof(nom_create_menu) / sizeof(nom_create_menu[0]);

   char **menu = toDynamicMenu(nom_create_menu, qty);

   char *menuTitle = "Inicio";
   int option = 0;

   do
   {
      system("cls");
      option = movimiento(menuTitle, menu, qty, qty, POSX, POSY, option);
      system("cls");

      if (option == 0)
      {
         showClientOptions(clientList);
      }

      if (option == 1)
      {
         showEquiposOptions(equipoList);
      }

      if (option == 2)
      {
         showProjectOptions(proyectoList, clientList);
      }

      if (option == 3)
      {
         showPropuestasOptions(propContractList, equiPropList, proyectoList);
      }

   } while (option != qty - 1);

   // Liberación de memoria de listas
   freeClientListComplete(clientList);
   freeEquipoListComplete(equipoList);
   freeProyectoListComplete(proyectoList);
   freePropContratoListComplete(propContractList);
   freeEquiPropListComplete(equiPropList);
   return 0;
}

//** MENU: CLIENTES **//

/*
   Función: showClientOptions
   Argumento: .
   Objetivo: Mostrar el menu de opciones para gestionar clientes.
   Retorno: Nada.
*/
void showClientOptions(CLIENTLIST *clientList)
{
   char nom_create_menu[][TAMAOPC] = {
       "Agregar",
       "Ver clientes",
       "<- Atras",
   };
   int qty = sizeof(nom_create_menu) / sizeof(nom_create_menu[0]);

   char **menu = toDynamicMenu(nom_create_menu, qty);

   char *menuTitle = "Manejo de clientes";
   int option = 0;

   do
   {
      system("cls");
      option = movimiento(menuTitle, menu, qty, qty, POSX, POSY, option);
      system("cls");

      if (option == 0)
      {
         // OPCIONES PARA AGREGAR CLIENTE
         showClientForm(clientList, ADD, 0);
      }

      if (option == 1)
      {
         // OPCIONES PARA VER CLIENTES
         if (clientList->length > 0)
         {
            showClientsMenu(clientList);
         }
      }

   } while (option != qty - 1);
}

/*
   Función: showClientForm
   Argumento:
      (CLIENTLIST *) clientList -> Lista de clientes.
      (int) mode -> Modo de operación. CREATE o EDIT.
      (int) position -> Posición del cliente en el indice.
   Objetivo: Mostrar formulario para añadir o editar cliente y proceder con su guardado, si el usuario acepta.
   Retorno: Nada.
*/
void showClientForm(CLIENTLIST *clientList, int mode, int position)
{
   CLIENTE cliente = {0};

   if (mode == EDIT)
   {
      NODOCLIENTE *clientNode = findClientByPosition(clientList, position);
      cliente = clientNode->cliente;
   }

   char menuSt[][TAMAOPC] = {
       "Id",
       "Primer Nombre",
       "Segundo Nombre",
       "Primer Apellido",
       "Segundo Apellido",
       "Documento de identidad",
       "Direccion",
       "Guardar",
       "<- Volver",
   };

   int option = 0;
   int qty = sizeof(menuSt) / sizeof(menuSt[0]);

   char **menu = toDynamicMenu(menuSt, qty);
   char *title = mode == ADD ? "Agregar cliente" : "Ver & editar cliente";

   FIELDPROP clientField = {0};
   clientField.type = LETTERS;
   clientField.hideCharacters = SHOWCHAR;

   int esp = LENTITLE;

   do
   {
      system("cls");
      option = movimiento(title, menu, qty, qty, POSX, POSY, option);

      if (option == 0)
      {
         //* Capturar id
         if (mode == ADD)
         {
            gotoxy(POSX + esp, POSY + option + 1);
            setColor(WHITE, RED);
            printf("El ID se genera autom%cticamente.", 160);
            colorDefault();
            Sleep(WARNINGSDELAY);
         }
         else
         {
            do
            {
               gotoxy(POSX + esp, POSY + option + 1);
               setColor(TFT, TFBG);
               printf("%s", cliente.idcliente);
               colorDefault();
            } while (getch() != ENTER);
         }
      }
      else if (option == 1)
      {
         //* Capturar primer nombre
         clientField.type = LETTERS;
         clientField.maxCharacters = LENPRINOMBRE;
         do
         {
            capfieldAlpha(cliente.primernomb, POSX + esp - 1, POSY + option + 1, clientField);

         } while (isEmptyField(cliente.primernomb, POSX + esp, POSY + option + 3));
      }
      else if (option == 2)
      {
         //* Capturar segundo nombre
         clientField.type = LETTERS;
         clientField.maxCharacters = LENSEGNOMBRE;
         do
         {
            capfieldAlpha(cliente.segnomb, POSX + esp - 1, POSY + option + 1, clientField);

         } while (isEmptyField(cliente.segnomb, POSX + esp, POSY + option + 3));
      }
      else if (option == 3)
      {
         //* Capturar primer apellido
         clientField.type = LETTERS;
         clientField.maxCharacters = LENPRIAPEL;
         do
         {
            capfieldAlpha(cliente.primerapel, POSX + esp - 1, POSY + option + 1, clientField);

         } while (isEmptyField(cliente.primerapel, POSX + esp, POSY + option + 3));
      }
      else if (option == 4)
      {
         //* Capturar segundo apellido
         clientField.type = LETTERS;
         clientField.maxCharacters = LENSEGAPEL;
         do
         {
            capfieldAlpha(cliente.segapel, POSX + esp - 1, POSY + option + 1, clientField);

         } while (isEmptyField(cliente.segapel, POSX + esp, POSY + option + 3));
      }
      else if (option == 5)
      {
         //* Capturar documento de identidad
         clientField.type = FULLTEXT;
         clientField.maxCharacters = MAXID;
         do
         {
            capfieldAlpha(cliente.docid, POSX + esp - 1, POSY + option + 1, clientField);

         } while (isEmptyField(cliente.docid, POSX + esp, POSY + option + 3));
      }
      else if (option == 6)
      {
         //* Capturar direccion
         clientField.type = LETTERS;
         clientField.maxCharacters = LENDIR;
         do
         {
            capfieldAlpha(cliente.direccion, POSX + esp - 1, POSY + option + 1, clientField);

         } while (isEmptyField(cliente.direccion, POSX + esp, POSY + option + 3));
      }
      else if (option == 7)
      {
         if (showConfirmMenu("Estas seguro?"))
         {
            if (mode == ADD)
            {
               //* FUNCION PARA AÑADIR CLIENTE
               generateClientId(clientList, cliente.idcliente);
               addClient(clientList, cliente);
            }
            else
            {
               //* FUNCION PARA GUARDAR CAMBIOS DE CLIENTE EDITADO
               updateClientByPosition(clientList, cliente, position);
            }

            saveClientListChanges(clientList);
            option = qty - 1;
         }
      }
   } while (option != qty - 1);
}

/*
   Función: showClientsMenu
   Argumento:
      (CLIENTLIST *) clientList -> Lista de clientes
   Objetivo: Mostrar menu-listado de los clientes registrados.
   Retorno: Nada.
*/
void showClientsMenu(CLIENTLIST *clientList)
{
   char **menu = getClientsNames(clientList);

   char *menuTitle = "Clientes guardados";
   int option = 0;
   int qty = clientList->length + 1;
   int showQty = DYNAMICITEMSTOSHOW;

   do
   {
      system("cls");
      option = movimiento(menuTitle, menu, qty, showQty, POSX, POSY, option);
      system("cls");

      if (option != qty - 1)
      {
         // ABRIR SUBMENU PARA MODIFICAR CLIENTE SELECCIONADO
         int suboption = showSelectedClientOptions(clientList, option);

         if (suboption == 0 || suboption == 1)
         {
            //  Volver al menu principal
            break;
         }
      }
   } while (option != qty - 1);

   freeDynamicMenu(menu, qty);
}

/*
   Función: showSelectedClientOptions
   Argumento:
      (CLIENTLIST *) clientList -> Lista de clientes
      (int) pos -> Indice de cliente seleccionado.
   Objetivo: Mostrar menu de opciones para el cliente seleccionado.
   Retorno: Nada.
*/
int showSelectedClientOptions(CLIENTLIST *clientList, int pos)
{
   char menuSt[][TAMAOPC] = {
       "Editar",
       "Eliminar",
       "<- Volver",
   };

   char *menuTitle = "Opciones del cliente seleccionado";
   int option = 0;
   int qty = sizeof(menuSt) / sizeof(menuSt[0]);

   char **menu = toDynamicMenu(menuSt, qty);

   NODOCLIENTE *cliente = findClientByPosition(clientList, pos);

   system("cls");
   option = movimiento(menuTitle, menu, qty, qty, POSX, POSY, option);
   system("cls");

   if (option == 0)
   {
      // EDITAR CLIENTE
      showClientForm(clientList, EDIT, pos);
   }
   else if (option == 1)
   {
      // ELIMINAR CLIENTE
      if (showConfirmMenu("Estas seguro?"))
      {
         deleteClientByPosition(clientList, pos);
         saveClientListChanges(clientList);
      }
   }

   return option;
}

//** MENU: EQUIPOS **//

/*
   Función: showEquiposOptions
   Argumento: (EQUIPOLIST *) equipoList.
   Objetivo: Mostrar el menu de opciones para gestionar equipos.
   Retorno: Nada.
*/
void showEquiposOptions(EQUIPOLIST *equipoList)
{
   char nom_create_menu[][TAMAOPC] = {
       "Agregar equipo",
       "Ver",
       "<- Atras",
   };

   char *menuTitle = "Manejo de equipos";
   int option = 0;
   int qty = sizeof(nom_create_menu) / sizeof(nom_create_menu[0]);

   char **menu = toDynamicMenu(nom_create_menu, qty);

   do
   {
      system("cls");
      option = movimiento(menuTitle, menu, qty, qty, POSX, POSY, option);
      system("cls");

      if (option == 0)
      {
         // OPCIONES PARA AGREGAR EQUIPO
         showEquipoForm(equipoList, ADD, 0);
      }

      if (option == 1)
      {
         // OPCIONES PARA VER EQUIPOS
         if (equipoList->length > 0)
         {
            showEquiposMenu(equipoList);
         }
      }

   } while (option != qty - 1);
}

/*
   Función: showEquipoForm
   Argumento:
      (EQUIPOLIST *) equipoList -> Lista de equipos.
      (int) mode -> Modo de operación. ADD o EDIT.
      (int) position -> Posición del equipo en el indice.
   Objetivo: Mostrar formulario para añadir o editar equipo y proceder con su guardado, si el usuario acepta.
   Retorno: Nada.
*/
void showEquipoForm(EQUIPOLIST *equipoList, int mode, int position)
{
   EQUIPO equipo = {0};

   if (mode == EDIT)
   {
      NODOEQUIPO *equipoNode = findEquipoByPosition(equipoList, position);
      equipo = equipoNode->equipo;
   }

   char menuSt[][TAMAOPC] = {
       "ID",
       "Descripcion",
       "Cantidad en inventario",
       "Cantidad prestados",
       "Precio de prestamo",
       "Costo de equipo",
       "Guardar",
       "<- Volver",
   };

   int option = 0;
   int qty = sizeof(menuSt) / sizeof(menuSt[0]);

   char **menu = toDynamicMenu(menuSt, qty);
   char *title = mode == ADD ? "Agregar equipo" : "Ver & editar equipo";

   FIELDPROP equipoField = {0};
   equipoField.type = LETTERS;
   equipoField.hideCharacters = SHOWCHAR;

   int esp = LENTITLE;

   do
   {
      system("cls");
      option = movimiento(title, menu, qty, qty, POSX, POSY, option);

      if (option == 0)
      {
         //* Capturar id
         if (mode == ADD)
         {
            gotoxy(POSX + esp, POSY + option + 1);
            setColor(WHITE, RED);
            printf("El ID se genera autom%cticamente.", 160);
            colorDefault();
            Sleep(WARNINGSDELAY);
         }
         else
         {
            do
            {
               gotoxy(POSX + esp, POSY + option + 1);
               setColor(TFT, TFBG);
               printf("%s", equipo.idequipo);
               colorDefault();
            } while (getch() != ENTER);
         }
      }
      else if (option == 1)
      {
         //* Capturar descripcion
         equipoField.type = LETTERS;
         equipoField.maxCharacters = LENDESC;
         do
         {
            capfieldAlpha(equipo.descripcion, POSX + esp - 1, POSY + option + 1, equipoField);

         } while (isEmptyField(equipo.descripcion, POSX + esp, POSY + option + 3));
      }
      else if (option == 2)
      {
         //* Capturar cantidad de inventario
         equipoField.type = NUMBERS;
         equipoField.hideCharacters = SHOWCHAR;
         equipoField.maxCharacters = NUMBERFIELDLEN;
         equipoField.numberDecimals = 0;

         char input[LINELEN] = {0};

         sprintf(input, "%d", equipo.cantinventario);

         do
         {
            capfieldAlpha(input, POSX + esp - 1, POSY + option + 1, equipoField);

         } while (!validNumeric(equipoField, input, POSX + esp, POSY + option + 3));

         equipo.cantinventario = atoi(input);
      }
      else if (option == 3)
      {
         //* Capturar cantidad prestados
         gotoxy(POSX + esp, POSY + option + 1);
         setColor(TFT, TFBG);
         printf("%d%*s", equipo.cantprestados, NUMBERFIELDLEN, "");
         colorDefault();
         Sleep(WARNINGSDELAY);
      }
      else if (option == 4)
      {
         //* Precio de prestamo
         equipoField.type = NUMBERS;
         equipoField.hideCharacters = SHOWCHAR;
         equipoField.maxCharacters = NUMBERFIELDLEN;
         equipoField.numberDecimals = 2;

         char input[LINELEN] = {0};

         sprintf(input, "%.2f", equipo.precioprestamo);

         do
         {
            capfieldAlpha(input, POSX + esp - 1, POSY + option + 1, equipoField);

         } while (!validNumeric(equipoField, input, POSX + esp, POSY + option + 3));

         equipo.precioprestamo = atof(input);
      }
      else if (option == 5)
      {
         //* Costo de equipo
         equipoField.type = NUMBERS;
         equipoField.hideCharacters = SHOWCHAR;
         equipoField.maxCharacters = NUMBERFIELDLEN;
         equipoField.numberDecimals = 2;

         char input[LINELEN] = {0};

         sprintf(input, "%.2f", equipo.costoequipo);

         do
         {
            capfieldAlpha(input, POSX + esp - 1, POSY + option + 1, equipoField);

         } while (!validNumeric(equipoField, input, POSX + esp, POSY + option + 3));

         equipo.costoequipo = atof(input);
      }
      else if (option == 6)
      {
         if (showConfirmMenu("Estas seguro?"))
         {
            if (mode == ADD)
            {
               //* FUNCION PARA AÑADIR CLIENTE
               generateEquipoId(equipoList, equipo.idequipo);
               addEquipo(equipoList, equipo);
            }
            else
            {
               //* FUNCION PARA GUARDAR CAMBIOS DE CLIENTE EDITADO
               updateEquipoByPosition(equipoList, equipo, position);
            }

            saveEquipoListChanges(equipoList);
            option = qty - 1;
         }
      }
   } while (option != qty - 1);
}

/*
   Función: showEquiposMenu
   Argumento:
      (EQUIPOLIST *) equipoList -> Lista de equipos
   Objetivo: Mostrar menu-listado de los equipos registrados.
   Retorno: Nada.
*/
void showEquiposMenu(EQUIPOLIST *equipoList)
{
   char **menu = getEquiposIDs(equipoList);

   char *menuTitle = "Equipos guardados";
   int option = 0;
   int qty = equipoList->length + 1;
   int showQty = DYNAMICITEMSTOSHOW;

   do
   {
      system("cls");
      option = movimiento(menuTitle, menu, qty, showQty, POSX, POSY, option);
      system("cls");

      if (option != qty - 1)
      {
         // ABRIR SUBMENU PARA MODIFICAR EQUIPO SELECCIONADO
         int suboption = showSelectedEquipoOptions(equipoList, option);

         if (suboption == 0 || suboption == 1)
         {
            // Volver al menu principal
            break;
         }
      }
   } while (option != qty - 1);

   freeDynamicMenu(menu, qty);
}

/*
   Función: showSelectedEquipoOptions
   Argumento:
      (EQUIPOLIST *) equipoList -> Lista de equipos
      (int) pos -> Indice de equipo seleccionado.
   Objetivo: Mostrar menu de opciones para el equipo seleccionado.
   Retorno: Nada.
*/
int showSelectedEquipoOptions(EQUIPOLIST *equipoList, int pos)
{
   char menuSt[][TAMAOPC] = {
       "Editar",
       "Eliminar",
       "<- Volver",
   };

   char *menuTitle = "Opciones de equipo seleccionado";
   int option = 0;
   int qty = sizeof(menuSt) / sizeof(menuSt[0]);

   char **menu = toDynamicMenu(menuSt, qty);

   system("cls");
   option = movimiento(menuTitle, menu, qty, qty, POSX, POSY, option);
   system("cls");

   if (option == 0)
   {
      //* EDITAR EQUIPO
      showEquipoForm(equipoList, EDIT, pos);
   }
   else if (option == 1)
   {
      //* ELIMINAR EQUIPO
      if (showConfirmMenu("Estas seguro?"))
      {
         deleteEquipoByPosition(equipoList, pos);
         saveEquipoListChanges(equipoList);
      }
   }

   return option;
}

//** MENU: PROYECTOS **//

/*
   Función: showProjectOptions
   Argumento: (PROYECTOLIST *) proyectoList -> Lista de proyectos
               (CLIENTLIST *) clientList -> Lista de clientes
   Objetivo: Mostrar el menu de opciones para gestionar proyectos.
   Retorno: Nada.
*/
void showProjectOptions(PROYECTOLIST *proyectoList, CLIENTLIST *clientList)
{
   char nom_create_menu[][TAMAOPC] = {
       "Crear proyecto",
       "Ver proyectos",
       "<- Atras",
   };

   char *menuTitle = "Manejo de proyectos";
   int option = 0;
   int qty = sizeof(nom_create_menu) / sizeof(nom_create_menu[0]);
   char **menu = toDynamicMenu(nom_create_menu, qty);

   do
   {
      system("cls");
      option = movimiento(menuTitle, menu, qty, qty, POSX, POSY, option);
      system("cls");

      if (option == 0)
      {
         // OPCIONES PARA CREAR PROYECTO
         showProyectoForm(proyectoList, clientList, ADD, 0);
      }

      if (option == 1)
      {
         // OPCIONES PARA VER PROYECTOS
         if (proyectoList->length > 0)
         {
            showProyectosMenu(proyectoList);
         }
      }

   } while (option != qty - 1);
}

/*
   Función: showProyectoForm
   Argumento:
      (PROYECTOLIST *) proyectoList -> Lista de proyectos.
      (CLIENTLIST *) clientList -> Lista de clientes.
      (int) mode -> Modo de operación. CREATE o EDIT.
      (int) position -> Posición del proyecto en el indice.
   Objetivo: Mostrar formulario para añadir o editar proyecto y proceder con su guardado, si el usuario acepta.
   Retorno: Nada.
*/
void showProyectoForm(PROYECTOLIST *proyectoList, CLIENTLIST *clientList, int mode, int position)
{
   PROYECTO proyecto = {0};

   if (mode == EDIT)
   {
      NODOPROYECTO *proyectoNode = findProyectoByPosition(proyectoList, position);
      proyecto = proyectoNode->proyecto;
   }

   char menuSt[][TAMAOPC] = {
       "ID",
       "Descripcion",
       "Cliente",
       "Guardar",
       "<- Volver",
   };

   int option = 0;
   int qty = sizeof(menuSt) / sizeof(menuSt[0]);

   char **menu = toDynamicMenu(menuSt, qty);
   char *title = mode == ADD ? "Agregar proyecto" : "Ver & editar proyecto";

   FIELDPROP proyectoField = {0};
   proyectoField.type = LETTERS;
   proyectoField.hideCharacters = SHOWCHAR;

   int esp = LENTITLE;

   do
   {
      system("cls");
      option = movimiento(title, menu, qty, qty, POSX, POSY, option);

      if (option == 0)
      {
         //* Capturar id
         if (mode == ADD)
         {
            gotoxy(POSX + esp, POSY + option + 1);
            setColor(WHITE, RED);
            printf("El ID se genera autom%cticamente.", 160);
            colorDefault();
            Sleep(WARNINGSDELAY);
         }
         else
         {
            do
            {
               gotoxy(POSX + esp, POSY + option + 1);
               setColor(TFT, TFBG);
               printf("%s", proyecto.idproyecto);
               colorDefault();
            } while (getch() != ENTER);
         }
      }
      else if (option == 1)
      {
         //* Capturar descripcion
         proyectoField.type = LETTERS;
         proyectoField.maxCharacters = LENDESC;
         do
         {
            capfieldAlpha(proyecto.descripcion, POSX + esp - 1, POSY + option + 1, proyectoField);

         } while (isEmptyField(proyecto.descripcion, POSX + esp, POSY + option + 3));
      }
      else if (option == 2)
      {
         //* Capturar id de cliente anidado
         if (mode == ADD)
         {
            proyectoField.type = NUMBERS;
            proyectoField.maxCharacters = MAXIDCLIENTE;
            do
            {
               capfieldAlpha(proyecto.idcliente, POSX + esp - 1, POSY + option + 1, proyectoField);

               if (findClientById(clientList->start, proyecto.idcliente) == NULL)
               {
                  gotoxy(POSX + esp, POSY + option + 3);
                  printf("Este cliente no existe.\n", 160);
                  Sleep(WARNINGSDELAY);
               }

            } while (isEmptyField(proyecto.idcliente, POSX + esp, POSY + option + 3) || findClientById(clientList->start, proyecto.idcliente) == NULL);
         }
         else //* EL CLIENTE ANIDADO NO ES EDITABLE ASI QUE SE MUESTRA EL ID SOLAMENTE
         {
            do
            {
               gotoxy(POSX + esp, POSY + option + 1);
               setColor(TFT, TFBG);
               printf("%s%*s", proyecto.idcliente, MAXIDCLIENTE, "");
               colorDefault();
            } while (getch() != ENTER);
         }
      }
      else if (option == 3)
      {
         if (showConfirmMenu("Estas seguro?"))
         {
            if (mode == ADD)
            {
               //* FUNCION PARA AÑADIR PROYECTO
               generateProyectoId(proyectoList, proyecto.idproyecto);
               addProyecto(proyectoList, proyecto);
            }
            else
            {
               //* FUNCION PARA GUARDAR CAMBIOS DE PROYECTO EDITADO
               updateProyectoByPosition(proyectoList, proyecto, position);
            }

            saveProyectoListChanges(proyectoList);
            option = qty - 1;
         }
      }
   } while (option != qty - 1);
}

/*
   Función: showProyectosMenu
   Argumento:
      (PROYECTOLIST *) proyectoList -> Lista de proyectos
   Objetivo: Mostrar menu-listado de los proyectos registrados.
   Retorno: Nada.
*/
void showProyectosMenu(PROYECTOLIST *proyectoList)
{
   char **menu = getProyectosIDs(proyectoList);

   char *menuTitle = "Proyectos registrados";
   int option = 0;
   int qty = proyectoList->length + 1;
   int showQty = DYNAMICITEMSTOSHOW;

   do
   {
      system("cls");
      option = movimiento(menuTitle, menu, qty, showQty, POSX, POSY, option);
      system("cls");

      if (option != qty - 1)
      {
         // ABRIR SUBMENU PARA MODIFICAR PROYECTO SELECCIONADO
         int suboption = showSelectedProyectoOptions(proyectoList, option);
         if (suboption == 0 || suboption == 1)
         {
            // Volver al menu principal
            break;
         }
      }
   } while (option != qty - 1);

   freeDynamicMenu(menu, qty);
}

/*
   Función: showSelectedProyectoOptions
   Argumento:
      (PROYECTOLIST *) proyectoList -> Lista de proyectos
      (int) pos -> Indice de proyecto seleccionado.
   Objetivo: Mostrar menu de opciones para el proyecto seleccionado.
   Retorno: Nada.
*/
int showSelectedProyectoOptions(PROYECTOLIST *proyectoList, int pos)
{
   char menuSt[][TAMAOPC] = {
       "Editar",
       "Eliminar",
       "<- Volver",
   };

   char *menuTitle = "Opciones de proyecto seleccionado";
   int option = 0;
   int qty = sizeof(menuSt) / sizeof(menuSt[0]);

   char **menu = toDynamicMenu(menuSt, qty);

   system("cls");
   option = movimiento(menuTitle, menu, qty, qty, POSX, POSY, option);
   system("cls");

   if (option == 0)
   {
      //* EDITAR PROYECTO
      showProyectoForm(proyectoList, NULL, EDIT, pos);
   }
   else if (option == 1)
   {
      //* ELIMINAR PROYECTO
      if (showConfirmMenu("Estas seguro?"))
      {
         deleteProyectoByPosition(proyectoList, pos);
         saveProyectoListChanges(proyectoList);
      }
   }

   return option;
}

//** MENU: PROPUESTAS DE CONTRATO **//
/*
   Función: showPropuestasOptions
   Argumento: (PROPCONTRACTOLIST *) propuestasList -> Lista de propuestas, (PROYECTOLIST *) proyectosList -> Lista de proyectos.
   Objetivo: Mostrar el menu de opciones para gestionar propuestas.
   Retorno: Nada.
*/
void showPropuestasOptions(PROPCONTRACTOLIST *propuestasList, EQUIPROPLIST *equipropList, PROYECTOLIST *proyectosList)
{
   char nom_create_menu[][TAMAOPC] = {
       "Agregar propuesta",
       "Activas",
       "Inactivas",
       "Cerradas",
       "<- Atras",
   };

   char *menuTitle = "Manejo de propuestas de contrato";
   int option = 0;
   int qty = sizeof(nom_create_menu) / sizeof(nom_create_menu[0]);

   char **menu = toDynamicMenu(nom_create_menu, qty);

   do
   {
      system("cls");
      option = movimiento(menuTitle, menu, qty, qty, POSX, POSY, option);
      system("cls");

      switch (option)
      {
      case 0:
         // OPCIONES PARA AGREGAR PROPUESTA
         showPropuestasForm(propuestasList, proyectosList, ADD, 0);
         break;

      case 1:
         // OPCIONES PARA VER PROPUESTAS ACTIVAS
         if (propuestasList->length > 0 && proyectosList->length > 0)
         {
            showPropuestasMenu(propuestasList, equipropList, PROPACTIVE);
         }
         break;

      case 2:
         // OPCIONES PARA VER PROPUESTAS INACTIVAS
         if (propuestasList->length > 0 && proyectosList->length > 0)
         {
            showPropuestasMenu(propuestasList, equipropList, PROPINACTIVE);
         }
         break;

      case 3:
         // OPCIONES PARA VER PROPUESTAS CERRADAS
         if (propuestasList->length > 0 && proyectosList->length > 0)
         {
            showPropuestasMenu(propuestasList, equipropList, PROPCLOSED);
         }
         break;
      }

   } while (option != qty - 1);
}

/*
   Función: showPropuestasForm
   Argumento:
      (PROPCONTRACTOLIST *) propuestaList -> Lista de propuestas.
      (PROYECTOLIST *) proyectosList -> Lista de proyectos.
      (int) mode -> Modo de operación. ADD o EDIT.
      (int) position -> Posición en el indice.
   Objetivo: Mostrar formulario para añadir o editar propuesta y proceder con su guardado, si el usuario acepta.
   Retorno: Nada.
*/
void showPropuestasForm(PROPCONTRACTOLIST *propuestaList, PROYECTOLIST *proyectosList, int mode, char id[MAXIDPROP])
{
   time_t tiempoActual;
   time(&tiempoActual);
   struct tm *localT = localtime(&tiempoActual);

   PROPCONTRACTO propuesta = {0};
   propuesta.fechapropcontrato.dia = localT->tm_mday;
   propuesta.fechapropcontrato.mes = localT->tm_mon + 1;
   propuesta.fechapropcontrato.agno = localT->tm_year + 1900;

   if (mode == EDIT)
   {
      NODOPROPCONTRACTO *propuestaNode = findPropContratoById(propuestaList, id);
      propuesta = propuestaNode->propcontrato;
   }

   char menuSt[][TAMAOPC] = {
       "ID",
       "Proyecto",
       "Fecha",
       "Estado", // CERRADO, INACTIVO Y ACTIVO
       "Guardar",
       "<- Volver",
   };

   int option = 0;
   int qty = sizeof(menuSt) / sizeof(menuSt[0]);

   char **menu = toDynamicMenu(menuSt, qty);
   char *title = mode == ADD ? "Agregar propuesta" : "Detalle de propuesta";

   FIELDPROP propuestaField = {0};
   propuestaField.type = LETTERS;
   propuestaField.hideCharacters = SHOWCHAR;

   int esp = LENTITLE;

   do
   {
      system("cls");
      option = movimiento(title, menu, qty, qty, POSX, POSY, option);

      if (option == 0)
      {
         //* Mostrar id
         if (mode == ADD)
         {
            gotoxy(POSX + esp, POSY + option + 1);
            setColor(WHITE, RED);
            printf("El ID se genera autom%cticamente.", 160);
            colorDefault();
            Sleep(WARNINGSDELAY);
         }
         else
         {
            do
            {
               gotoxy(POSX + esp, POSY + option + 1);
               setColor(TFT, TFBG);
               printf("%s", propuesta.idpropcontrato);
               colorDefault();
            } while (getch() != ENTER);
         }
      }
      else if (option == 1)
      {
         //* Capturar id de proyecto anidado
         if (mode == ADD)
         {
            propuestaField.type = NUMBERS;
            propuestaField.maxCharacters = MAXIDPROY;
            do
            {
               capfieldAlpha(propuesta.idproyecto, POSX + esp - 1, POSY + option + 1, propuestaField);

               if (findProyectoById(proyectosList, propuesta.idproyecto) == NULL)
               {
                  gotoxy(POSX + esp, POSY + option + 3);
                  printf("Este proyecto no existe.\n", 160);
                  Sleep(WARNINGSDELAY);
               }

            } while (isEmptyField(propuesta.idproyecto, POSX + esp, POSY + option + 3) || findProyectoById(proyectosList, propuesta.idproyecto) == NULL);
         }
         else
         {
            //* Mostrar id de proyecto anidado
            do
            {
               gotoxy(POSX + esp, POSY + option + 1);
               setColor(TFT, TFBG);
               printf("%s", propuesta.idproyecto);
               colorDefault();
            } while (getch() != ENTER);
         }
      }
      else if (option == 2)
      {
         if (mode == ADD)
         {
            //* Capturar fecha de propuesta de contrato
            propuestaField.type = DATEF;
            propuestaField.maxCharacters = LENDATE;
            propuestaField.hideCharacters = SHOWCHAR;

            char propuestaDate[LENDATE] = {0, 0, '/', 0, 0, '/', 0, 0, 0, 0};

            if (propuesta.fechapropcontrato.dia != 0 && propuesta.fechapropcontrato.mes != 0 && propuesta.fechapropcontrato.agno != 0)
            {
               sprintf(propuestaDate, "%02d/%02d/%04d", propuesta.fechapropcontrato.dia, propuesta.fechapropcontrato.mes, propuesta.fechapropcontrato.agno);
            }

            do
            {
               capfieldAlpha(propuestaDate, POSX + esp - 1, POSY + option + 1, propuestaField);
               sscanf(propuestaDate, "%d/%d/%d", &propuesta.fechapropcontrato.dia, &propuesta.fechapropcontrato.mes, &propuesta.fechapropcontrato.agno);

               if (!dateValidation(propuesta.fechapropcontrato.dia, propuesta.fechapropcontrato.mes, propuesta.fechapropcontrato.agno))
               {
                  gotoxy(POSX + esp, POSY + option + 3);
                  printf("Fecha de nacimiento inv%clida. Intente de nuevo.\n", 160);
                  Sleep(WARNINGSDELAY);
               }

            } while (!dateValidation(propuesta.fechapropcontrato.dia, propuesta.fechapropcontrato.mes, propuesta.fechapropcontrato.agno));
         }
         else
         {
            //* Mostrar fecha de propuesta
            do
            {
               gotoxy(POSX + esp, POSY + option + 1);
               setColor(TFT, TFBG);
               printf("%02d/%02d/%04d", propuesta.fechapropcontrato.dia, propuesta.fechapropcontrato.mes, propuesta.fechapropcontrato.agno);
               colorDefault();
            } while (getch() != ENTER);
         }
      }
      else if (option == 3)
      {
         //* Mostrar estado de propuesta
         if (mode == ADD)
         {
            gotoxy(POSX + esp, POSY + option + 1);
            setColor(WHITE, RED);
            printf("El estado al generar una propuesta es inactivo.");
            colorDefault();
            Sleep(WARNINGSDELAY);
         }
         else
         {
            do
            {
               gotoxy(POSX + esp, POSY + option + 1);
               setColor(TFT, TFBG);
               printf("%s", propuesta.status == PROPCLOSED ? "Cerrado" : propuesta.status == PROPINACTIVE ? "Inactivo"
                                                                                                          : "Activo");
               colorDefault();
            } while (getch() != ENTER);
         }
      }
      else if (option == 4)
      {
         if (showConfirmMenu("Estas seguro?"))
         {
            if (mode == ADD)
            {
               //* FUNCION PARA AÑADIR PROPUESTA
               generatePropContratoId(propuestaList, propuesta.idpropcontrato);
               propuesta.status = PROPINACTIVE;
               addPropContrato(propuestaList, propuesta);
            }
            else
            {
               //* FUNCION PARA GUARDAR CAMBIOS DE PROPUESTA EDITADA
               updatePropContrato(propuestaList, propuesta);
            }

            savePropContratoListChanges(propuestaList);
            option = qty - 1;
         }
      }
   } while (option != qty - 1);
}

/*
   Función: showPropuestasMenu
   Argumento:
      (PROPCONTRACTOLIST *) propuestasList -> Lista de propuesta
      (char) status -> Estado de la propuesta.
   Objetivo: Mostrar menu-listado de las propuestas registradas.
   Retorno: Nada.
*/
void showPropuestasMenu(PROPCONTRACTOLIST *propuestasList, EQUIPROPLIST *equipropList, char status)
{
   char **menu = getPropContratosIDsByStatus(propuestasList, status);

   char menuTitle[20];
   sprintf(menuTitle, "Propuestas %s", status == PROPCLOSED ? "cerradas" : status == PROPINACTIVE ? "inactivas"
                                                                                                  : "activas");
   int option = 0;

   int qty = 0;
   while (menu[qty] != NULL)
   {
      qty++;
   }
   qty += 1;

   int showQty = DYNAMICITEMSTOSHOW;

   do
   {
      system("cls");
      option = movimiento(menuTitle, menu, qty - 1, showQty, POSX, POSY, option);
      system("cls");

      if (option != qty - 2)
      {
         // ABRIR SUBMENU PARA MODIFICAR PROPUESTA SELECCIONADA
         int suboption = showSelectedPropuestasOptions(propuestasList, equipropList, menu[option]);
         if (suboption == 0 || suboption == 1)
         {
            // Volver al menu principal
            break;
         }
      }
   } while (option != qty - 2);

   freeDynamicMenu(menu, qty);
}

/*
   Función: showSelectedPropuestasOptions
   Argumento:
      (PROPCONTRACTOLIST *) propuestasList -> Lista de propuestas
      (char [MAXIDPROP]) id -> ID de propuesta seleccionado.
   Objetivo: Mostrar menu de opciones para la propuesta seleccionado.
   Retorno: Nada.
*/
int showSelectedPropuestasOptions(PROPCONTRACTOLIST *propuestasList, EQUIPROPLIST *equipropList, char id[MAXIDPROP])
{
   char menuSt[][TAMAOPC] = {
       "Agregar equipos",
       "Ver equipos",
       "Detalle",
       "Eliminar",
       "<- Volver",
   };

   char *menuTitle = "Opciones de propuesta seleccionada";
   int option = 0;
   int qty = sizeof(menuSt) / sizeof(menuSt[0]);

   char **menu = toDynamicMenu(menuSt, qty);

   system("cls");
   option = movimiento(menuTitle, menu, qty, qty, POSX, POSY, option);
   system("cls");

   if (option == 0)
   {
      //* EDITAR PROYECTO
      showEquiPropForm(propuestasList, equipropList, ADD, id, NULL); // showProyectoForm(proyectoList, NULL, EDIT, pos);
   }
   else if (option == 2)
   {
      showPropuestasForm(propuestasList, NULL, EDIT, id);
   }
   else if (option == 3)
   {
      //* ELIMINAR PROYECTO
      if (showConfirmMenu("Estas seguro?"))
      {
         deletePropContrato(propuestasList, id);
         savePropContratoListChanges(propuestasList);
      }
   }

   return option;
}

/*
   Función: showEquiPropForm
   Argumento:
      (PROPCONTRACTOLIST *) propuestaList -> Lista de propuestas.
      (EQUIPROPLIST *) equipropList -> Lista de proyectos.
      (int) mode -> Modo de operación. ADD o EDIT.
      (int) position -> Posición en el indice.
   Objetivo: Mostrar formulario para añadir o editar propuesta y proceder con su guardado, si el usuario acepta.
   Retorno: Nada.
*/
void showEquiPropForm(PROPCONTRACTOLIST *propuestaList, EQUIPROPLIST *equipropList, int mode, char idProp[MAXIDPROP], char idEquiProp[MAXIDEQUIPO])
{
   EQUIPROP equiprop = {0};

   /*if (mode == EDIT)
   {
      NODOPROPCONTRACTO *propuestaNode = findPropContratoById(propuestaList, id);
      propuesta = propuestaNode->propcontrato;
   }*/

   char menuSt[][TAMAOPC] = {
       "ID de equipo",
       "Cantidad",
       "Guardar",
       "<- Volver",
   };

   int option = 0;
   int qty = sizeof(menuSt) / sizeof(menuSt[0]);

   char **menu = toDynamicMenu(menuSt, qty);
   char *title = mode == ADD ? "Agregar propuesta" : "Detalle de propuesta";

   FIELDPROP Field = {0};
   Field.type = LETTERS;
   Field.hideCharacters = SHOWCHAR;

   int esp = LENTITLE;

   do
   {
      system("cls");
      option = movimiento(title, menu, qty, qty, POSX, POSY, option);

      if (option == 0)
      {
         //* Capturar id de equipo anidado
         if (mode == ADD)
         {
            Field.type = NUMBERS;
            Field.maxCharacters = MAXIDEQUIPO;
            do
            {
               capfieldAlpha(equiprop.idequipo, POSX + esp - 1, POSY + option + 1, Field);

               /* if (findProyectoById(proyectosList, propuesta.idproyecto) == NULL)
                {
                   gotoxy(POSX + esp, POSY + option + 3);
                   printf("Este proyecto no existe.\n", 160);
                   Sleep(WARNINGSDELAY);
                }*/

            } while (isEmptyField(equiprop.idequipo, POSX + esp, POSY + option + 3) /*|| findProyectoById(proyectosList, propuesta.idproyecto) == NULL*/);
         }
         else
         {
            //* Mostrar id de proyecto anidado
            do
            {
               gotoxy(POSX + esp, POSY + option + 1);
               setColor(TFT, TFBG);
               printf("%s", equiprop.idequipo);
               colorDefault();
            } while (getch() != ENTER);
         }
      }
      else if (option == 1)
      {
         //* Capturar cantidad de inventario
         Field.type = NUMBERS;
         Field.hideCharacters = SHOWCHAR;
         Field.maxCharacters = NUMBERFIELDLEN;
         Field.numberDecimals = 0;

         char input[LINELEN] = {0};

         sprintf(input, "%d", equiprop.cantidad);

         do
         {
            capfieldAlpha(input, POSX + esp - 1, POSY + option + 1, Field);

         } while (!validNumeric(Field, input, POSX + esp, POSY + option + 3));

         equiprop.cantidad = atoi(input);
      }
      else if (option == 2)
      {
         if (showConfirmMenu("Estas seguro?"))
         {
            if (mode == ADD)
            {
               //* FUNCION PARA AÑADIR PROPUESTA
               strcpy(equiprop.idpropcontrato, idProp);
               addEquiProp(equipropList, equiprop);
            }

            saveEquiPropListChanges(equipropList);
            option = qty - 1;
         }
      }
   } while (option != qty - 1);
}

//** MENU API **//

/*
   Función: showOpcXY
   Argumento:
      (char *) title -> Titulo del menu
      (char [][TAMAOPC]) menu -> Opciones del menu
      (int) n -> Cantidad de opciones
      (int) showQty -> Cantidad de opciones a mostrar
      (int) py -> Posición vertical del cursor
      (int) px -> Posición horizontal del cursor.
   Objetivo: Mostrar el menu y sus opciones
   Retorno: Nada.
*/
void showOpcXY(char *title, char **menu, int n, int showQty, int px, int py, int opcsel)
{
   int ind, start, end;
   int totalTitleWidth = LENTITLE;
   int esp = totalTitleWidth - strlen(title);

   if (showQty > n)
   {
      showQty = n;
   }

   start = opcsel - showQty / 2;
   if (start < 0)
      start = 0;
   if (start > n - showQty)
      start = n - showQty;
   end = start + showQty;
   if (end > n)
      end = n;

   gotoxy(px, py);
   setColor(CET, CEF);
   printf("%s%*s", title, esp, "");

   for (ind = start; ind < end; ind++)
   {
      setColor(CT, CF);
      gotoxy(px, py + ind - start + 1);
      if (opcsel == ind)
         setColor(CTS, CFS);
      printf("%s%*s", menu[ind], totalTitleWidth - strlen(menu[ind]), "");
   }

   colorDefault();
}

/*
   Función: movimiento
   Argumento:
      (char **) menu -> Opciones del menu
      (int) n -> Cantidad de opciones
      (int) showQty -> Cantidad de opciones a mostrar
      (int) px -> Posición horizontal del cursor
      (int) py -> Posición vertical del cursor
      (int) opcsel -> Opcion seleccionada.
   Objetivo: Mostrar el menu y sus opciones
   Retorno: Nada.
*/
int movimiento(char *title, char **menu, int n, int showQty, int px, int py, int opcsel)
{
   char tecla;
   int salir = 1;

   _setcursortype(0);
   do
   {
      showOpcXY(title, menu, n, showQty, px, py, opcsel);
      do
      {
         tecla = getch();
      } while (tecla != ESC && tecla != ENTER && tecla != ARRIBA && tecla != ABAJO);

      if (tecla != ESC)
      {

         if (tecla == ARRIBA)
         {
            if (opcsel != 0)
               opcsel--;
            else
               opcsel = n - 1;
         }
         if (tecla == ABAJO)
         {
            if (opcsel < n - 1)
               opcsel++;
            else
               opcsel = 0;
         }
      }
      else
         opcsel = n - 1;
   } while (tecla != ESC && tecla != ENTER);
   _setcursortype(100);

   return opcsel;
}

/*
   Función: toDynamicMenu
   Argumento:
      (char [][TAMAOPC]) in -> Arreglo de cadena de carácteres estático.
      (int) qty -> Cantidad de elementos del arreglo.
   Objetivo: Devolver arreglo de cadena de carácteres dinámico para el menú.
   Retorno: (char **) Arreglo de cadena de cáracteres dinámico.
*/
char **toDynamicMenu(char in[][TAMAOPC], int qty)
{
   char **menuDinamico = (char **)malloc(qty * sizeof(char *));

   for (int i = 0; i < qty; i++)
   {
      menuDinamico[i] = in[i];
   }

   return menuDinamico;
}

/*
   Función: freeDynamicMenu
   Argumento:
      (char **) menu -> Arreglo de cadena de carácteres dinámico de menu.
      (int) qty -> Cantidad de elementos del arreglo.
   Objetivo: Liberar memoria de cadena de carácteres y arreglo dinamico.
   Retorno: Nada.
*/
void freeDynamicMenu(char **menu, int qty)
{
   for (int i = 0; i < qty; i++)
   {
      free(menu[i]);
   }

   free(menu);
}

/*
   Función: showConfirmMenu
   Argumento:
      (char *) title -> Titulo para menu.
   Objetivo: Mostrar menu de opciones para confirmar una accion.
   Retorno: 1 si se selecciona "si" y 0 si se selecciona "no".
*/
int showConfirmMenu(char *title)
{
   char menuSt[][TAMAOPC] = {
       "Si",
       "No",
   };

   int option = 0;
   int qty = sizeof(menuSt) / sizeof(menuSt[0]);

   char **menu = toDynamicMenu(menuSt, qty);

   system("cls");
   option = movimiento(title, menu, qty, qty, POSX, POSY, option);
   system("cls");

   return !option;
}

//** CAPFIELD API **//

/*
   Función: showField
   Argumento: (char *) s -> Cadena de texto, (int) hide -> Ocultar carácteres o no, (int) pos -> Posición de carácter, (int) n -> Cantidad de carácteres, (int) x -> Posición horizontal del cursor, (int) y -> Posición vertical del cursor.
   Objetivo: Mostrar campo de texto.
   Retorno: Nada.
*/
void showField(char *s, FIELDPROP Fieldprops, int pos, int x, int y)
{
   int ind;

   setColor(TFT, TFBG);
   for (ind = 0; ind < Fieldprops.maxCharacters; ind++)
   {
      gotoxy(x + ind + 1, y);

      if (*(s + ind) && !Fieldprops.hideCharacters)
         printf("%c", *(s + ind));
      else if (*(s + ind) && Fieldprops.hideCharacters)
         printf("*");
      else
         printf(" ");
   }
   colorDefault();
   gotoxy(x + pos + 1, y);

   return;
}

/*
   Función: capfieldAlpha
   Argumento: (char *) str -> Cadena de texto, (int) n -> Cantidad de carácteres, (int) x -> Posición horizontal del cursor, (int) y -> Posición vertical del cursor.
   Objetivo: Captar carácteres para campo de texto.
   Retorno: Nada.
*/
void capfieldAlpha(char *str, int x, int y, FIELDPROP Fieldprops)
{
   int ind = strlen(str), punto = 0;
   char chr;

   Fieldprops.maxCharacters = Fieldprops.maxCharacters - 1;

   _setcursortype(100);
   do
   {
      showField(str, Fieldprops, ind, x, y);
      do
      {
         chr = getch();
      } while (!((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z') || (chr >= '0' && chr <= '9')) && chr != ENTER && chr != ESC && chr != IZQUIERDA && chr != BKSP && chr != DERECHA && chr != PUNTO && (chr == ESP && Fieldprops.hideCharacters));

      if (chr == DERECHA)
      {
         if (ind < Fieldprops.maxCharacters - 1)
            ind++;
      }
      else
      {

         if (chr == IZQUIERDA)
         {
            if (ind > 0)
               ind--;
         }
         else
         {

            if (chr != ENTER && chr != ESC)
            {
               if (chr == BKSP && ind)
               {
                  if (Fieldprops.type == DATEF) // BORRADO PARA CAMPOS DE TIPO FECHA
                  {
                     if (*(str + ind - 1) == '/')
                     {
                        ind--;
                     }

                     ind--;

                     // Reemplaza el carácter en la posición ind - 1 por un espacio
                     *(str + ind) = ' ';
                  }
                  else // BORRADO NORMAL
                  {
                     ind--;
                     strcpy(str + ind, str + ind + 1);
                  }
               }
               else
               {
                  if (ind < Fieldprops.maxCharacters)
                  {
                     if ((*(str + ind) == '/') && Fieldprops.type == DATEF)
                     {
                        ind++;
                     }

                     if (isValidChar(Fieldprops, chr))
                     {
                        *(str + ind) = chr;
                        ind++;
                     }
                  }
               }
            }
         }
      }

   } while (chr != ENTER && chr != ESC);

   if (chr != ESC)
      *(str + ind) = '\0';

   return;
}

/*
   Función: isEmptyField
   Argumento:
      (char *) str -> Campo a evaluar.
   Objetivo: Chequear si campo esta vacio.
   Retorno: (int) 1 si esta vacio y 0 si no lo es.
*/
int isEmptyField(char *str, int px, int py)
{
   if (strlen(str) < 1)
   {
      gotoxy(px, py);
      printf("Debe completar el campo.\n", 160);
      Sleep(WARNINGSDELAY);
      return 1;
   }

   return 0;
}

/*
   Función: int isValidChar
   Argumento: (FIELDPROP) fieldProps -> Propiedades del campo, (char) c -> Carácter a evaluar.
   Objetivo: Validar caracter en relacion al tipo de campo.
   Retorno: Positivo si es valido en base al tipo de campo, lo contrario si no lo es
*/
int isValidChar(FIELDPROP fieldProps, char c)
{
   return (fieldProps.type == FULLTEXT || ((fieldProps.type == NUMBERS || fieldProps.type == DATEF) && (c >= '0' && c <= '9') || (c == PUNTO && fieldProps.numberDecimals > 0)) || (fieldProps.type == LETTERS && (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ESP));
}

/*
   Función: dateValidation
   Argumento: (int) day -> Dia suministrado, (int) month -> Mes suministrado, (int) year -> Año suministrado.
   Objetivo: Validar si es una fecha válida.
   Retorno: (int) 1 si es válida y 0 si no lo es.
*/
int dateValidation(int day, int month, int year)
{
   int monthsDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

   if (month == 2 && isLeapYear(year))
   {
      monthsDays[1] = 29;
   }

   if (month < 1 || month > 12)
   {
      return 0;
   }

   if (day < 1 || day > monthsDays[month - 1])
   {
      return 0;
   }

   return 1;
}

/*
   Función: validNumeric
   Argumento: (FIELDPROP) field -> Campo, (char *) str -> Cadena de texto suministrada.
   Objetivo: Validar campo numérico.
   Retorno: (int) 1 si es válido y 0 si no lo es.
*/
int validNumeric(FIELDPROP field, char *str, int px, int py)
{
   // Verificar si el campo es numérico
   if (field.type != NUMBERS)
   {
      gotoxy(px, py);
      printf("No puede haber caracteres numéricos.\n", 160);
      Sleep(WARNINGSDELAY / 2);
      return 0;
   }

   int puntuations = 0;

   for (int i = 0; str[i]; i++)
   {
      if (str[i] == PUNTO)
      {
         puntuations++;
      }

      if (!(str[i] >= '0' && str[i] <= '9') && str[i] != PUNTO)
      {
         gotoxy(px, py);
         printf("No puede haber caracteres no numericos.\n", 160);
         Sleep(WARNINGSDELAY / 2);
         return 0;
      }
   }

   char *afterPuntuation = strchr(str, PUNTO);
   int charAfterPuntuation = 0;

   if (afterPuntuation != NULL)
   {
      charAfterPuntuation = strlen(afterPuntuation + 1);
   }

   // Verificar si los dígitos decimales que hay presentes son igual a la cantidad estipulada
   if (charAfterPuntuation > field.numberDecimals)
   {
      gotoxy(px, py);
      printf("Te excediste de digitos decimales. Max: %d\n", field.numberDecimals);
      Sleep(WARNINGSDELAY / 2);
      return 0;
   }

   return 1;
}

//** Clientes Management **//

/*
   Función: createClientList
   Argumento: Nada.
   Objetivo: Crear una lista de clientes y asignar espacio en memoria.
   Retorno: (CLIENTLIST *) Lista creada.
*/
CLIENTLIST *createClientList()
{
   CLIENTLIST *newList = (CLIENTLIST *)malloc(sizeof(CLIENTLIST));

   if (newList == NULL)
   {
      printf("Error al crear la lista.\n");
      exit(1);
   }

   newList->start = NULL;
   newList->end = NULL;
   newList->length = 0;

   return newList;
}

/*
   Función: createClientNode
   Argumento: (CLIENT) client -> Datos del cliente.
   Objetivo: Crear nodo de cliente.
   Retorno: (NODOCLIENTE *) Nodo de cliente.
*/
NODOCLIENTE *createClientNode(CLIENTE client)
{
   NODOCLIENTE *newNode = (NODOCLIENTE *)malloc(sizeof(NODOCLIENTE));

   if (newNode == NULL)
   {
      printf("Error al crear el nodo cliente.\n");
      exit(1);
   }

   newNode->cliente = client;
   newNode->sig = NULL;
   newNode->ant = NULL;

   return newNode;
}

/*
Función: generateClientId.
Argumentos:
   CLIENTLIST *list: Listado de nodos de clientes.
   char id[MAXIDCLIENTE]: Variable que almacena el id a generar.
Objetivo: Generar un id random para un cliente.
Retorno: Nada.
*/
void generateClientId(CLIENTLIST *list, char id[MAXIDCLIENTE])
{
   char *lastIdStr = getLastClientId(list);
   long long lastId = 0;

   if (lastIdStr != NULL)
   {
      lastId = atoll(lastIdStr);
   }

   lastId++;

   snprintf(id, MAXIDCLIENTE, "%lld", lastId);
}

/*
Función: getLastClientId.
Argumentos:
   (CLIENTLIST *) list -> Listado de nodos de clientes.
Objetivo: Obtener el id del último cliente añadido.
Retorno: Nada.
*/
char *getLastClientId(CLIENTLIST *list)
{
   NODOCLIENTE *current = list->start;
   char *lastId = NULL;

   if (current == NULL)
   {
      return NULL;
   }

   while (current != NULL)
   {
      lastId = current->cliente.idcliente;
      current = current->sig;
   }

   return lastId;
}

/*
   Función: findClientById
   Argumento: (NODOCLIENTE *) start -> Cabeza de lista de clientes, (char [MAXIDCLIENTE]) id -> ID del cliente.
   Objetivo: Revisar si un id de cliente ya existe.
   Retorno: (NODOCLIENTE *) Nodo del cliente encontrado o NULL si no existe.
*/
NODOCLIENTE *findClientById(NODOCLIENTE *start, char id[MAXIDCLIENTE])
{
   NODOCLIENTE *current = start;

   while (current != NULL)
   {
      if (strcmp(current->cliente.idcliente, id) == 0)
      {
         return current; // Nodo encontrado
      }
      current = current->sig;
   }

   return NULL; // Nodo no encontrado
}

/*
   Función: findClientByPosition
   Argumento:
      (CLIENTLIST *) list -> Lista de clientes.
      (int) posicion -> Posición del cliente en el indice.
   Objetivo: Revisar si un id de cliente ya existe.
   Retorno: (NODOCLIENTE *) Nodo del cliente encontrado o NULL si no existe.
*/
NODOCLIENTE *findClientByPosition(CLIENTLIST *list, int position)
{
   if (position < 0 || position > list->length)
   {
      return NULL;
   }

   NODOCLIENTE *current = list->start;
   for (int i = 0; i < position; i++)
   {
      current = current->sig;
   }

   return current;
}

/*
   Función: addClient
   Argumento: (CLIENTLIST *) list -> Lista de clientes, (CLIENTE) client -> Datos del cliente (NODOCLIENTE).
   Objetivo: Añadir un cliente nuevo.
   Retorno: Nada.
*/
void addClient(CLIENTLIST *list, CLIENTE client)
{
   NODOCLIENTE *newNode = createClientNode(client);

   if (list->start == NULL)
   {
      list->start = newNode;
      list->end = newNode;
   }
   else
   {
      newNode->ant = list->end;
      list->end->sig = newNode;
      list->end = newNode;
   }

   list->length++;
}

/*
   Función: getClientNames
   Argumento:
      (CLIENTLIST *) list -> Lista de clientes.
   Objetivo: Agrupar nombres de los clientes en arreglo de cadena de cáracteres
   Retorno: (char **) Arreglo de cadena de carácteres de nombres y apellidos de clientes.
*/
char **getClientsNames(CLIENTLIST *list)
{
   if (list->length == 0)
   {
      return NULL;
   }

   char **names = (char **)malloc((list->length + 1) * sizeof(char *));

   NODOCLIENTE *current = list->start;

   int i;
   for (i = 0; i < list->length; i++)
   {
      if (current == NULL)
      {
         break;
      }

      names[i] = (char *)malloc(strlen(current->cliente.primernomb) + strlen(current->cliente.primerapel) + 3);
      strcpy(names[i], current->cliente.primernomb);
      strcat(names[i], " ");
      strcat(names[i], current->cliente.primerapel);

      current = current->sig;
   }

   char *text = "<- Volver";
   names[i] = (char *)malloc(strlen(text) + 1);
   strcpy(names[i], text);

   return names;
}

/*
   Función: deleteClientByPosition
   Argumento:
      (CLIENTELIST *) list -> Lista de clientes.
      (int) position -> Posición del cliente en el índice.
   Objetivo: Eliminar cliente en base a su posición en el índice.
   Retorno: Nada.
*/
void deleteClientByPosition(CLIENTLIST *list, int position)
{
   if (position >= list->length || position < 0)
   {
      printf("Posici%cn fuera de rango.\n", 162);
      return;
   }

   NODOCLIENTE *current = list->start;

   if (position == 0)
   {
      list->start = current->sig;
      free(current);
      list->length--;
      return;
   }

   for (int i = 0; current != NULL && i < position - 1; i++)
   {
      current = current->sig;
   }

   if (current == NULL || current->sig == NULL)
   {
      return;
   }

   NODOCLIENTE *sig = current->sig->sig;

   free(current->sig);
   current->sig = sig;

   list->length--;
}

/*
   Función: updateClientByPosition
   Argumento:
      (CLIENTLIST *) list -> Lista de clientes.
      (CLIENTE) cliente -> Datos del cliente.
      (int) position -> Posición del cliente seleccionado.
   Objetivo: Actualizar cliente seleccionado con nuevos datos.
   Retorno: Nada.
*/
void updateClientByPosition(CLIENTLIST *list, CLIENTE cliente, int position)
{
   if (position >= list->length || position < 0)
   {
      printf("Posici%cn fuera de rango.\n", 162);
      return;
   }

   NODOCLIENTE *current = list->start;
   for (int i = 0; i < position; i++)
   {
      current = current->sig;
   }

   if (current == NULL)
   {
      printf("Cliente no encontrado.");
      return;
   }

   current->cliente = cliente;
}

/*
   Función: freeClientListComplete
   Argumento: (CLIENTLIST *) list -> Lista de clientes.
   Objetivo: Liberar memoria de lista y nodos dentro de la lista.
   Retorno: Nada.
*/
void freeClientListComplete(CLIENTLIST *list)
{
   if (list != NULL)
   {
      NODOCLIENTE *actual = list->start;
      while (actual != NULL)
      {
         NODOCLIENTE *temp = actual;
         actual = actual->sig;
         free(temp);
      }
      free(list);
   }
}

//** EQUIPOS MANAGEMENT **//
/*
   Función: createEquipoList
   Argumento: Nada.
   Objetivo: Crear una lista de equipos y asignar espacio en memoria.
   Retorno: (EQUIPOLIST *) Lista creada.
*/
EQUIPOLIST *createEquipoList()
{
   EQUIPOLIST *newList = (EQUIPOLIST *)malloc(sizeof(EQUIPOLIST));

   if (newList == NULL)
   {
      printf("Error al crear la lista.\n");
      exit(1);
   }

   newList->start = NULL;
   newList->end = NULL;
   newList->length = 0;

   return newList;
}

/*
   Función: createEquipoNode
   Argumento: (EQUIPO) equpo -> Datos del equipo.
   Objetivo: Crear nodo de equipo.
   Retorno: (NODOEQUIPO *) Nodo de equipo.
*/
NODOEQUIPO *createEquipoNode(EQUIPO equipo)
{
   NODOEQUIPO *newNode = (NODOEQUIPO *)malloc(sizeof(NODOEQUIPO));

   if (newNode == NULL)
   {
      printf("Error al crear el nodo cliente.\n");
      exit(1);
   }

   newNode->equipo = equipo;
   newNode->sig = NULL;
   newNode->ant = NULL;

   return newNode;
}

/*
   Función: addEquipo
   Argumento: (EQUIPOLIST *) list -> Lista de equipos, (EQUIPO) equipo -> Datos del equipo.
   Objetivo: Añadir un equipo nuevo.
   Retorno: Nada.
*/
void addEquipo(EQUIPOLIST *list, EQUIPO equipo)
{
   NODOEQUIPO *newNode = createEquipoNode(equipo);

   if (list->start == NULL)
   {
      list->start = newNode;
      list->end = newNode;
   }
   else
   {
      newNode->ant = list->end;
      list->end->sig = newNode;
      list->end = newNode;
   }

   list->length++;
}

/*
   Función: updateEquipoByPosition
   Argumento:
      (EQUIPOLIST *) list -> Lista de equipos.
      (EQUIPO) equipo -> Datos del equipo.
      (int) position -> Posición del equipo seleccionado.
   Objetivo: Actualizar equipo seleccionado con nuevos datos.
   Retorno: Nada.
*/
void updateEquipoByPosition(EQUIPOLIST *list, EQUIPO equipo, int position)
{
   if (position >= list->length || position < 0)
   {
      printf("Posici%cn fuera de rango.\n", 162);
      return;
   }

   NODOEQUIPO *current = list->start;
   for (int i = 0; i < position; i++)
   {
      current = current->sig;
   }

   if (current == NULL)
   {
      printf("Equipo no encontrado.");
      return;
   }

   current->equipo = equipo;
}

/*
   Función: deleteEquipoByPosition
   Argumento:
      (EQUIPOLIST *) list -> Lista de equipos.
      (int) position -> Posición del equipo en el índice.
   Objetivo: Eliminar equipo en base a su posición en el índice.
   Retorno: Nada.
*/
void deleteEquipoByPosition(EQUIPOLIST *list, int position)
{
   if (position >= list->length || position < 0)
   {
      printf("Posici%cn fuera de rango.\n", 162);
      return;
   }

   NODOEQUIPO *current = list->start;

   if (position == 0)
   {
      list->start = current->sig;
      free(current);
      list->length--;
      return;
   }

   for (int i = 0; current != NULL && i < position - 1; i++)
   {
      current = current->sig;
   }

   if (current == NULL || current->sig == NULL)
   {
      return;
   }

   NODOEQUIPO *sig = current->sig->sig;

   free(current->sig);
   current->sig = sig;

   list->length--;
}

/*
Función: generateEquipoId.
Argumentos:
   EQUIPOLIST *list: Listado de nodos de equipos.
   char id[MAXIDEQUIPO]: Variable que almacena el id a generar.
Objetivo: Generar un id random para un equipo.
Retorno: Nada.
*/
void generateEquipoId(EQUIPOLIST *list, char id[MAXIDEQUIPO])
{
   char *lastIdStr = getLastEquipoId(list);
   int lastId = 0;

   if (lastIdStr != NULL)
   {
      lastId = atoi(lastIdStr);
   }

   lastId++;
   snprintf(id, MAXIDEQUIPO, "%d", lastId);
}

/*
Función: getLastEquipoId.
Argumentos:
   (EQUIPOLIST *) list -> Listado de nodos de equipos.
Objetivo: Obtener el id del último equipo añadido.
Retorno: Nada.
*/
char *getLastEquipoId(EQUIPOLIST *list)
{
   NODOEQUIPO *current = list->start;
   char *lastId = NULL;

   if (current == NULL)
   {
      return NULL;
   }

   while (current != NULL)
   {
      lastId = current->equipo.idequipo;
      current = current->sig;
   }

   return lastId;
}

/*
   Función: getEquiposIDs
   Argumento:
      (EQUIPOLIST *) list -> Lista de equipos.
   Objetivo: Agrupar IDs de los equipos en arreglo de cadena de cáracteres
   Retorno: (char **) Arreglo de cadena de carácteres de IDs de equipos.
*/
char **getEquiposIDs(EQUIPOLIST *list)
{
   if (list->length == 0)
   {
      return NULL;
   }

   char **items = (char **)malloc((list->length + 1) * sizeof(char *));

   NODOEQUIPO *current = list->start;

   int i;
   for (i = 0; i < list->length; i++)
   {
      if (current == NULL)
      {
         break;
      }

      items[i] = (char *)malloc(strlen(current->equipo.idequipo) + 1);
      strcpy(items[i], current->equipo.idequipo);

      current = current->sig;
   }

   char *text = "<- Volver";
   items[i] = (char *)malloc(strlen(text) + 1);
   strcpy(items[i], text);

   return items;
}

/*
   Función: findEquipoByPosition
   Argumento:
      (EQUIPOLIST *) list -> Lista de equipos.
      (int) posicion -> Posición del equipo en el indice.
   Objetivo: Revisar si un id de equipo ya existe.
   Retorno: (NODOEQUIPO *) Nodo del equipo encontrado o NULL si no existe.
*/
NODOEQUIPO *findEquipoByPosition(EQUIPOLIST *list, int position)
{
   if (position < 0 || position > list->length)
   {
      return NULL;
   }

   NODOEQUIPO *current = list->start;
   for (int i = 0; i < position; i++)
   {
      current = current->sig;
   }

   return current;
}

/*
   Función: freeEquipoListComplete
   Argumento: (EQUIPOLIST *) list -> Lista de equipos.
   Objetivo: Liberar memoria de lista y nodos dentro de la lista.
   Retorno: Nada.
*/
void freeEquipoListComplete(EQUIPOLIST *list)
{
   if (list != NULL)
   {
      NODOEQUIPO *actual = list->start;
      while (actual != NULL)
      {
         NODOEQUIPO *temp = actual;
         actual = actual->sig;
         free(temp);
      }
      free(list);
   }
}

//** PROYECTO MANAGEMENT **//
/*
   Función: createProyectoList
   Argumento: Nada.
   Objetivo: Crear una lista de proyectos y asignar espacio en memoria.
   Retorno: (PROYECTOLIST *) Lista creada.
*/
PROYECTOLIST *createProyectoList()
{
   PROYECTOLIST *newList = (PROYECTOLIST *)malloc(sizeof(PROYECTOLIST));

   if (newList == NULL)
   {
      printf("Error al crear la lista.\n");
      exit(1);
   }

   newList->start = NULL;
   newList->end = NULL;
   newList->length = 0;

   return newList;
}

/*
   Función: createProyectoNode
   Argumento: (PROYECTO) proyecto -> Datos del proyecto.
   Objetivo: Crear nodo de proyecto.
   Retorno: (NODOPROYECTO *) Nodo de proyecto.
*/
NODOPROYECTO *createProyectoNode(PROYECTO proyecto)
{
   NODOPROYECTO *newNode = (NODOPROYECTO *)malloc(sizeof(NODOPROYECTO));

   if (newNode == NULL)
   {
      printf("Error al crear el nodo proyecto.\n");
      exit(1);
   }

   newNode->proyecto = proyecto;
   newNode->sig = NULL;
   newNode->ant = NULL;

   return newNode;
}

/*
   Función: addProyecto
   Argumento: (PROYECTOLIST *) list -> Lista de proyectos, (PROYECTO) proyecto -> Datos del proyecto.
   Objetivo: Añadir un proyecto nuevo.
   Retorno: Nada.
*/
void addProyecto(PROYECTOLIST *list, PROYECTO proyecto)
{
   NODOPROYECTO *newNode = createProyectoNode(proyecto);

   if (list->start == NULL)
   {
      list->start = newNode;
      list->end = newNode;
   }
   else
   {
      newNode->ant = list->end;
      list->end->sig = newNode;
      list->end = newNode;
   }

   list->length++;
}

/*
   Función: updateProyectoByPosition
   Argumento:
      (PROYECTOLIST *) list -> Lista de equipos.
      (PROYECTO) proyecto -> Datos del proyecto.
      (int) position -> Posición del proyecto seleccionado.
   Objetivo: Actualizar proyecto seleccionado con nuevos datos.
   Retorno: Nada.
*/
void updateProyectoByPosition(PROYECTOLIST *list, PROYECTO proyecto, int position)
{
   if (position >= list->length || position < 0)
   {
      printf("Posici%cn fuera de rango.\n", 162);
      return;
   }

   NODOPROYECTO *current = list->start;
   for (int i = 0; i < position; i++)
   {
      current = current->sig;
   }

   if (current == NULL)
   {
      printf("Proyecto no encontrado.");
      return;
   }

   current->proyecto = proyecto;
}

/*
   Función: deleteProyectoByPosition
   Argumento:
      (PROYECTOLIST *) list -> Lista de proyectos.
      (int) position -> Posición del proyecto en el índice.
   Objetivo: Eliminar proyecto en base a su posición en el índice.
   Retorno: Nada.
*/
void deleteProyectoByPosition(PROYECTOLIST *list, int position)
{
   if (position >= list->length || position < 0)
   {
      printf("Posici%cn fuera de rango.\n", 162);
      return;
   }

   NODOPROYECTO *current = list->start;

   if (position == 0)
   {
      list->start = current->sig;
      free(current);
      list->length--;
      return;
   }

   for (int i = 0; current != NULL && i < position - 1; i++)
   {
      current = current->sig;
   }

   if (current == NULL || current->sig == NULL)
   {
      return;
   }

   NODOPROYECTO *sig = current->sig->sig;

   free(current->sig);
   current->sig = sig;

   list->length--;
}

/*
Función: generateProyectoId.
Argumentos:
   PROYECTOLIST *list: Listado de nodos de proyectos.
   char id[MAXIDPROY]: Variable que almacena el id a generar.
Objetivo: Generar un id random para un proyecto.
Retorno: Nada.
*/
void generateProyectoId(PROYECTOLIST *list, char id[MAXIDPROY])
{
   char *lastIdStr = getLastProyectoId(list);
   int lastId = 0;

   if (lastIdStr != NULL)
   {
      lastId = atoi(lastIdStr);
   }

   lastId++;

   snprintf(id, MAXIDPROY, "%d", lastId);
}

/*
Función: getLastProyectoId.
Argumentos:
   (PROYECTOLIST *) list -> Listado de nodos de proyectos.
Objetivo: Obtener el id del último proyecto añadido.
Retorno: Nada.
*/
char *getLastProyectoId(PROYECTOLIST *list)
{
   NODOPROYECTO *current = list->start;
   char *lastId = NULL;

   if (current == NULL)
   {
      return NULL;
   }

   while (current != NULL)
   {
      lastId = current->proyecto.idproyecto;
      current = current->sig;
   }

   return lastId;
}

/*
   Función: getProyectosIDs
   Argumento:
      (PROYECTOLIST *) list -> Lista de proyectos.
   Objetivo: Agrupar IDs de los proyectos en arreglo de cadena de cáracteres
   Retorno: (char **) Arreglo de cadena de carácteres de IDs de proyectos.
*/
char **getProyectosIDs(PROYECTOLIST *list)
{
   if (list->length == 0)
   {
      return NULL;
   }

   char **items = (char **)malloc((list->length + 1) * sizeof(char *));

   NODOPROYECTO *current = list->start;

   int i;
   for (i = 0; i < list->length; i++)
   {
      if (current == NULL)
      {
         break;
      }

      items[i] = (char *)malloc(strlen(current->proyecto.idproyecto) + 1);
      strcpy(items[i], current->proyecto.idproyecto);

      current = current->sig;
   }

   char *text = "<- Volver";
   items[i] = (char *)malloc(strlen(text) + 1);
   strcpy(items[i], text);

   return items;
}

/*
   Función: findProyectoByPosition
   Argumento:
      (PROYECTOLIST *) list -> Lista de proyectos.
      (int) posicion -> Posición del proyecto en el indice.
   Objetivo: Revisar si un id de proyecto ya existe.
   Retorno: (NODOPROYECTO *) Nodo del proyecto encontrado o NULL si no existe.
*/
NODOPROYECTO *findProyectoByPosition(PROYECTOLIST *list, int position)
{
   if (position < 0 || position > list->length)
   {
      return NULL;
   }

   NODOPROYECTO *current = list->start;
   for (int i = 0; i < position; i++)
   {
      current = current->sig;
   }

   return current;
}

/*
   Función: findProyectoById
   Argumento: (PROYECTOLIST *) list -> Lista de proyectos, (char [MAXIDPROY]) id -> ID del proyecto.
   Objetivo: Buscar un proyecto por su id.
   Retorno: (NODOCLIENTE *) Nodo del proyecto encontrado o NULL si no existe.
*/
NODOPROYECTO *findProyectoById(PROYECTOLIST *list, char id[MAXIDPROY])
{
   if (list->length == 0)
   {
      return NULL;
   }

   NODOPROYECTO *current = list->start;

   while (current != NULL)
   {
      if (strcmp(current->proyecto.idproyecto, id) == 0)
      {
         return current; // Nodo encontrado
      }
      current = current->sig;
   }

   return NULL; // Nodo no encontrado
}

/*
   Función: freeProyectoListComplete
   Argumento: (PROYECTOLIST *) list -> Lista de proyectos.
   Objetivo: Liberar memoria de lista y nodos dentro de la lista.
   Retorno: Nada.
*/
void freeProyectoListComplete(PROYECTOLIST *list)
{
   if (list != NULL)
   {
      NODOPROYECTO *actual = list->start;
      while (actual != NULL)
      {
         NODOPROYECTO *temp = actual;
         actual = actual->sig;
         free(temp);
      }
      free(list);
   }
}

//** PROPUESTA DE CONTRATO MANAGEMENT **//
/*
   Función: createPropContratoList
   Argumento: Nada.
   Objetivo: Crear una lista de propuestas de contrato y asignar espacio en memoria.
   Retorno: (PROPCONTRACTOLIST *) Lista creada.
*/
PROPCONTRACTOLIST *createPropContratoList()
{
   PROPCONTRACTOLIST *newList = (PROPCONTRACTOLIST *)malloc(sizeof(PROPCONTRACTOLIST));

   if (newList == NULL)
   {
      printf("Error al crear la lista.\n");
      exit(1);
   }

   newList->start = NULL;
   newList->end = NULL;
   newList->length = 0;

   return newList;
}

/*
   Función: createPropContratoNode
   Argumento: (PROPCONTRACTO) propuesta -> Datos del propcontracto.
   Objetivo: Crear nodo de propcontracto.
   Retorno: (NODOPROPCONTRACTO *) Nodo de propcontracto.
*/
NODOPROPCONTRACTO *createPropContratoNode(PROPCONTRACTO propuesta)
{
   NODOPROPCONTRACTO *newNode = (NODOPROPCONTRACTO *)malloc(sizeof(NODOPROPCONTRACTO));

   if (newNode == NULL)
   {
      printf("Error al crear el nodo proyecto.\n");
      exit(1);
   }

   newNode->propcontrato = propuesta;
   newNode->sig = NULL;
   newNode->ant = NULL;

   return newNode;
}

/*
   Función: addPropContrato
   Argumento: (PROPCONTRACTOLIST *) list -> Lista de propuestas de contratos, (PROPCONTRACTO) propcontracto -> Datos de la propuesta de contrato.
   Objetivo: Añadir una propuesta de contrato nuevo.
   Retorno: Nada.
*/
void addPropContrato(PROPCONTRACTOLIST *list, PROPCONTRACTO propuesta)
{
   NODOPROPCONTRACTO *newNode = createPropContratoNode(propuesta);

   if (list->start == NULL)
   {
      list->start = newNode;
      list->end = newNode;
   }
   else
   {
      newNode->ant = list->end;
      list->end->sig = newNode;
      list->end = newNode;
   }

   list->length++;
}

/*
   Función: updatePropContrato
   Argumento:
      (PROPCONTRACTOLIST *) list -> Lista de propuestas.
      (PROPCONTRACTO) propuesta -> Datos de la propuesta.
   Objetivo: Actualizar propuesta seleccionadoacon nuevos datos.
   Retorno: Nada.
*/
void updatePropContrato(PROPCONTRACTOLIST *list, PROPCONTRACTO propuesta)
{
   NODOPROPCONTRACTO *current = findPropContratoById(list, propuesta.idpropcontrato);

   current->propcontrato = propuesta;
}

/*
   Función: deletePropContrato
   Argumento:
      (PROPCONTRACTOLIST *) list -> Lista.
      (char [MAXIDPROP]) id -> ID del propuesta.
   Objetivo: Eliminar elemento de lista en base a su id.
   Retorno: Nada.
*/
void deletePropContrato(PROPCONTRACTOLIST *list, char id[MAXIDPROP])
{
   if (list->length == 0 || strlen(id) == 0)
   {
      printf("Error: La lista está vacía o el ID no es válido.\n");
      return;
   }

   NODOPROPCONTRACTO *toDelete = findPropContratoById(list, id);
   if (toDelete == NULL)
   {
      printf("Error: No se encontró el contrato con el ID especificado.\n");
      return;
   }

   if (toDelete == list->start)
   {
      list->start = toDelete->sig;
   }
   else
   {
      NODOPROPCONTRACTO *prev = list->start;
      while (prev != NULL && prev->sig != toDelete)
      {
         prev = prev->sig;
      }
      if (prev != NULL)
      {
         prev->sig = toDelete->sig;
      }
   }

   free(toDelete);
   list->length--;
}

/*
Función: generatePropContratoID.
Argumentos:
   PROPCONTRACTOLIST *list: Listado de nodos de propuestas.
   char id[MAXIDPROP]: Variable que almacena el id a generar.
Objetivo: Generar un id random para una propuesta.
Retorno: Nada.
*/
void generatePropContratoId(PROPCONTRACTOLIST *list, char id[MAXIDPROP])
{
   char *lastIdStr = getLastPropContratoId(list);
   long long lastId = 0;

   if (lastIdStr != NULL)
   {
      lastId = atoll(lastIdStr);
   }

   lastId++;

   snprintf(id, MAXIDPROP, "%lld", lastId);
}

/*
Función: getLastPropContratoId.
Argumentos:
   (PROPCONTRACTOLIST *) list -> Listado de nodos de propuestas.
Objetivo: Obtener el id de la última propuesta añadida.
Retorno: (char *) Ultimo id de la lista.
*/
char *getLastPropContratoId(PROPCONTRACTOLIST *list)
{
   NODOPROPCONTRACTO *current = list->start;
   char *lastId = NULL;

   if (current == NULL)
   {
      return NULL;
   }

   while (current != NULL)
   {
      lastId = current->propcontrato.idpropcontrato;
      current = current->sig;
   }

   return lastId;
}

/*
   Función: getPropContratosIDsByStatus
   Argumento:
      (PROPCONTRACTOLIST *) list -> Lista de propuestas.
      (char) status -> Estado de la propuesta.
   Objetivo: Agrupar IDs de las propuestas en arreglo de cadena de cáracteres
   Retorno: (char **) Arreglo de cadena de carácteres de IDs de propuestas.
*/
char **getPropContratosIDsByStatus(PROPCONTRACTOLIST *list, char status)
{
   if (list->length == 0)
   {
      return NULL;
   }

   int count = 0;
   NODOPROPCONTRACTO *current = list->start;
   while (current != NULL)
   {
      if (current->propcontrato.status == status)
      {
         count++;
      }
      current = current->sig;
   }

   char **items = (char **)malloc((count + 2) * sizeof(char *));

   int i = 0;
   current = list->start;
   while (current != NULL && i < count)
   {
      if (current->propcontrato.status == status)
      {
         items[i] = (char *)malloc(strlen(current->propcontrato.idpropcontrato) + 1);
         if (items[i] != NULL)
         {
            strcpy(items[i], current->propcontrato.idpropcontrato);
            i++;
         }
      }
      current = current->sig;
   }

   char *text = "<- Volver";
   items[count] = (char *)malloc(strlen(text) + 1);
   if (items[count] != NULL)
   {
      strcpy(items[count], text);
   }

   items[count + 1] = NULL;

   return items;
}

/*
   Función: findPropContratoById
   Argumento: (PROPCONTRACTOLIST *) list -> Lista, (char [MAXIDPROP]) id -> ID.
   Objetivo: Buscar un propuesta por su id.
   Retorno: (NODOPROPCONTRACTO *) Nodo encontrado o NULL si no existe.
*/
NODOPROPCONTRACTO *findPropContratoById(PROPCONTRACTOLIST *list, char id[MAXIDPROP])
{
   if (list->length == 0)
   {
      return NULL;
   }

   NODOPROPCONTRACTO *current = list->start;

   while (current != NULL)
   {
      if (strcmp(current->propcontrato.idpropcontrato, id) == 0)
      {
         return current; // Nodo encontrado
      }
      current = current->sig;
   }

   return NULL; // Nodo no encontrado
}
/*
   Función: freePropContratoListComplete
   Argumento: (PROPCONTRACTOLIST *) list -> Lista de propuestas de contratos.
   Objetivo: Liberar memoria de lista y nodos dentro de la lista.
   Retorno: Nada.
*/
void freePropContratoListComplete(PROPCONTRACTOLIST *list)
{
   if (list != NULL)
   {
      NODOPROPCONTRACTO *actual = list->start;
      while (actual != NULL)
      {
         NODOPROPCONTRACTO *temp = actual;
         actual = actual->sig;
         free(temp);
      }
      free(list);
   }
}

//** EQUIPO EN PROPUESTA MANAGEMENT **//
/*
   Función: createEquiPropList
   Argumento: Nada.
   Objetivo: Crear una lista de equipo en propuestas de contrato y asignar espacio en memoria.
   Retorno: (EQUIPROPLIST *) Lista creada.
*/
EQUIPROPLIST *createEquiPropList()
{
   EQUIPROPLIST *newList = (EQUIPROPLIST *)malloc(sizeof(EQUIPROPLIST));

   if (newList == NULL)
   {
      printf("Error al crear la lista.\n");
      exit(1);
   }

   newList->start = NULL;
   newList->end = NULL;
   newList->length = 0;

   return newList;
}

/*
   Función: createEquiPropNode
   Argumento: (EQUIPROP) equipo en propuesta -> Datos del equiprop.
   Objetivo: Crear nodo de equiprop.
   Retorno: (NODOEQUIPROP *) Nodo de equiprop.
*/
NODOEQUIPROP *createEquiPropNode(EQUIPROP equiprop)
{
   NODOEQUIPROP *newNode = (NODOEQUIPROP *)malloc(sizeof(NODOEQUIPROP));

   if (newNode == NULL)
   {
      printf("Error al crear el nodo proyecto.\n");
      exit(1);
   }

   newNode->equiprop = equiprop;
   newNode->sig = NULL;
   newNode->ant = NULL;

   return newNode;
}

/*
   Función: addEquiProp
   Argumento: (EQUIPROPLIST *) list -> Lista de equipos en propuesta, (EQUIPROP) equiprop -> Datos del equipo en propuesta.
   Objetivo: Añadir un equipo en propuesta nuevo.
   Retorno: Nada.
*/
void addEquiProp(EQUIPROPLIST *equiPropList, EQUIPROP equiprop)
{
   NODOEQUIPROP *newNode = createEquiPropNode(equiprop);

   if (equiPropList->start == NULL)
   {
      equiPropList->start = newNode;
      equiPropList->end = newNode;
   }
   else
   {
      newNode->ant = equiPropList->end;
      equiPropList->end->sig = newNode;
      equiPropList->end = newNode;
   }

   equiPropList->length++;
}

/*
   Función: deleteEquiProp
   Argumento:
      (PROPCONTRACTOLIST *) propuestasList -> Lista.
      (EQUIPROPLIST *) equiPropList -> Lista de equipos en propuesta.
      (char [MAXIDPROP]) idProp -> ID de propuesta.
      (char [MAXIDEQUIPO]) id -> ID de equipo.
   Objetivo: Eliminar elemento de lista en base a su id.
   Retorno: Nada.
*/
void deleteEquiProp(PROPCONTRACTOLIST *propuestasList, EQUIPROPLIST *equiPropList, char idProp[MAXIDPROP], char id[MAXIDEQUIPO])
{
}

/*
   Función: getEquiposProp
   Argumento:
      (PROPCONTRACTOLIST *) list -> Lista de propuestas.
      (EQUIPROPLIST *) list -> Lista de equipos en propuesta.
      (char [MAXIDPROP]) idProp -> ID de la propuesta.
   Objetivo: Agrupar IDs de los equipos en propuestas de la propuesta del id suministrado en arreglo de cadena de cáracteres
   Retorno: (char **) Arreglo de cadena de carácteres de IDs de equipos en propuestas.
*/
char **getEquiposProp(PROPCONTRACTOLIST *propuestasList, EQUIPROPLIST *equipropList, char idProp[MAXIDPROP])
{
   if (equipropList->length == 0)
   {
      return NULL;
   }

   int count = 0;
   NODOEQUIPROP *current = equipropList->start;
   while (current != NULL)
   {
      if (current->equiprop.idpropcontrato == idProp)
      {
         count++;
      }
      current = current->sig;
   }

   char **items = (char **)malloc((count + 2) * sizeof(char *));

   int i = 0;
   current = equipropList->start;
   while (current != NULL && i < count)
   {
      if (current->equiprop.idpropcontrato == idProp)
      {
         items[i] = (char *)malloc(strlen(current->equiprop.idpropcontrato) + 1);
         if (items[i] != NULL)
         {
            strcpy(items[i], current->equiprop.idpropcontrato);
            i++;
         }
      }
      current = current->sig;
   }

   char *text = "<- Volver";
   items[count] = (char *)malloc(strlen(text) + 1);
   if (items[count] != NULL)
   {
      strcpy(items[count], text);
   }

   items[count + 1] = NULL;

   return items;
}

/*
   Función: freeEquiPropListComplete
   Argumento: (EQUIPROPLIST *) list -> Lista de equipos en propuestas de contratos.
   Objetivo: Liberar memoria de lista y nodos dentro de la lista.
   Retorno: Nada.
*/
void freeEquiPropListComplete(EQUIPROPLIST *list)
{
   if (list != NULL)
   {
      NODOEQUIPROP *actual = list->start;
      while (actual != NULL)
      {
         NODOEQUIPROP *temp = actual;
         actual = actual->sig;
         free(temp);
      }
      free(list);
   }
}

//** FILE MANAGEMENT **//
/*
   Función: loadClientList
   Argumento:
      (CLIENTLIST *) list -> Lista de clientes.
   Objetivo: Cargar archivo de lista de clientes.
   Retorno: Nada.
*/
void loadClientList(CLIENTLIST *list)
{
   FILE *fp = fopen(CLIENTES_FILENAME, "rb");

   if (fp == NULL)
   {
      setColor(WHITE, BLUE);
      printf("Error al abrir el archivo de clientes o el archivo no existe. \n");
      Sleep(WARNINGSDELAY / 2);
      colorDefault();
      system("cls");
      return;
   }

   CLIENTE cliente;

   while (fread(&cliente, sizeof(cliente), 1, fp) == 1)
   {
      addClient(list, cliente);
   }

   fclose(fp);
}

/*
   Función: loadEquipoList
   Argumento:
      (EQUIPOLIST *) list -> Lista de equipos.
   Objetivo: Cargar archivo de lista de equipos.
   Retorno: Nada.
*/
void loadEquipoList(EQUIPOLIST *list)
{
   FILE *fp = fopen(EQUIPOS_FILENAME, "rb");

   if (fp == NULL)
   {
      setColor(WHITE, BLUE);
      printf("Error al abrir el archivo de equipos o el archivo no existe. \n");
      Sleep(WARNINGSDELAY / 2);
      colorDefault();
      system("cls");
      return;
   }

   EQUIPO equipo;

   while (fread(&equipo, sizeof(equipo), 1, fp) == 1)
   {
      addEquipo(list, equipo);
   }

   fclose(fp);
}

/*
   Función: loadProyectoList
   Argumento:
      (PROYECTOLIST *) list -> Lista de proyectos.
   Objetivo: Cargar archivo de lista de proyectos.
   Retorno: Nada.
*/
void loadProyectoList(PROYECTOLIST *list)
{
   FILE *fp = fopen(PROYECTOS_FILENAME, "rb");

   if (fp == NULL)
   {
      setColor(WHITE, BLUE);
      printf("Error al abrir el archivo de proyectos o el archivo no existe. \n");
      Sleep(WARNINGSDELAY / 2);
      colorDefault();
      system("cls");
      return;
   }

   PROYECTO proyecto;

   while (fread(&proyecto, sizeof(proyecto), 1, fp) == 1)
   {
      addProyecto(list, proyecto);
   }

   fclose(fp);
}

/*
   Función: loadPropContratoList
   Argumento:
      (PROPCONTRACTOLIST *) list -> Lista de propuestas de contrato.
   Objetivo: Cargar archivo de lista de propuestas de contrato.
   Retorno: Nada.
*/
void loadPropContratoList(PROPCONTRACTOLIST *list)
{
   FILE *fp = fopen(PROPUESTAS_FILENAME, "rb");

   if (fp == NULL)
   {
      setColor(WHITE, BLUE);
      printf("Error al abrir el archivo de propuestas de contrato o el archivo no existe. \n");
      Sleep(WARNINGSDELAY / 2);
      colorDefault();
      system("cls");
      return;
   }

   PROPCONTRACTO propuesta;

   while (fread(&propuesta, sizeof(propuesta), 1, fp) == 1)
   {
      addPropContrato(list, propuesta);
   }

   fclose(fp);
}

/*
   Función: loadEquiPropList
   Argumento:
      (EQUIPROPLIST *) list -> Lista de equipos en propuestas de contrato.
   Objetivo: Cargar archivo de lista de equipos en propuestas de contrato.
   Retorno: Nada.
*/
void loadEquiPropList(EQUIPROPLIST *list)
{
   FILE *fp = fopen(EQUIPROP_FILENAME, "rb");

   if (fp == NULL)
   {
      setColor(WHITE, BLUE);
      printf("Error al abrir el archivo de equipos en propuestas de contrato o el archivo no existe. \n");
      Sleep(WARNINGSDELAY / 2);
      colorDefault();
      system("cls");
      return;
   }

   EQUIPROP equiprop;

   while (fread(&equiprop, sizeof(equiprop), 1, fp) == 1)
   {
      addEquiProp(list, equiprop);
      fclose(fp);
   }
}
/*
   Función: saveClientListChanges
   Argumento:
      (CLIENTLIST *) list -> Lista de clientes.
   Objetivo: Guardar cambios de lista de clientes en archivo de almacenamiento.
   Retorno: Nada.
*/
void saveClientListChanges(CLIENTLIST *list)
{
   FILE *fp = fopen(CLIENTES_FILENAME, "wb");
   if (fp == NULL)
   {
      printf("Error al abrir el archivo de clientes");
      exit(1);
   }

   NODOCLIENTE *current = list->start;
   while (current != NULL)
   {
      fwrite(&(current->cliente), sizeof(CLIENTE), 1, fp);
      current = current->sig;
   }

   fclose(fp);
}

/*
   Función: saveEquipoListChanges
   Argumento:
      (EQUIPOLIST *) list -> Lista de equipos.
   Objetivo: Guardar cambios de lista de equipos en archivo de almacenamiento.
   Retorno: Nada.
*/
void saveEquipoListChanges(EQUIPOLIST *list)
{
   FILE *fp = fopen(EQUIPOS_FILENAME, "wb");
   if (fp == NULL)
   {
      printf("Error al abrir el archivo de equipos");
      exit(1);
   }

   NODOEQUIPO *current = list->start;
   while (current != NULL)
   {
      fwrite(&(current->equipo), sizeof(EQUIPO), 1, fp);
      current = current->sig;
   }

   fclose(fp);
}

/*
   Función: saveProyectoListChanges
   Argumento:
      (PROYECTOLIST *) list -> Lista de proyectos.
   Objetivo: Guardar cambios de lista de proyectos en archivo de almacenamiento.
   Retorno: Nada.
*/
void saveProyectoListChanges(PROYECTOLIST *list)
{
   FILE *fp = fopen(PROYECTOS_FILENAME, "wb");
   if (fp == NULL)
   {
      printf("Error al abrir el archivo de proyectos");
      exit(1);
   }

   NODOPROYECTO *current = list->start;
   while (current != NULL)
   {
      fwrite(&(current->proyecto), sizeof(PROYECTO), 1, fp);
      current = current->sig;
   }

   fclose(fp);
}

/*
   Función: savePropContratoListChanges
   Argumento:
      (PROPCONTRACTOLIST *) list -> Lista de propuestas.
   Objetivo: Guardar cambios de lista de propuestas en archivo de almacenamiento.
   Retorno: Nada.
*/
void savePropContratoListChanges(PROPCONTRACTOLIST *list)
{
   FILE *fp = fopen(PROPUESTAS_FILENAME, "wb");
   if (fp == NULL)
   {
      printf("Error al abrir el archivo de propuestas de contrato");
      exit(1);
   }

   NODOPROPCONTRACTO *current = list->start;
   while (current != NULL)
   {
      fwrite(&(current->propcontrato), sizeof(PROPCONTRACTO), 1, fp);
      current = current->sig;
   }

   fclose(fp);
}

/*
   Función: saveEquiPropListChanges
   Argumento:
      (EQUIPROPLIST *) list -> Lista de equipos en propuestas.
   Objetivo: Guardar cambios de lista de equipos en propuestas en archivo de almacenamiento.
   Retorno: Nada.
*/
void saveEquiPropListChanges(EQUIPROPLIST *list)
{
   FILE *fp = fopen(EQUIPROP_FILENAME, "wb");
   if (fp == NULL)
   {
      printf("Error al abrir el archivo de equipos en propuestas de contrato");
      exit(1);
   }

   NODOEQUIPROP *current = list->start;
   while (current != NULL)
   {
      fwrite(&(current->equiprop), sizeof(EQUIPROP), 1, fp);
      current = current->sig;
   }

   fclose(fp);
}

//** UTILS **//

/*
   Función: void setColor
   Argumento: (int) ct -> Color del texto, (int) cf -> Color del fondo.
   Objetivo: Asignar color de fondo y texto del programa.
   Retorno: Nada.
*/
void setColor(int ct, int cf)
{
   textbackground(cf);
   textcolor(ct);
}

/*
   Función: void colorDefault
   Argumento: Nada.
   Objetivo: Asignar los colores de texto y fondo por defecto en el programa.
   Retorno: Nada.
*/
void colorDefault()
{
   setColor(LIGHTGRAY, BLACK);
}

/*
   Función: isLeapYear
   Argumento: (int) year -> Año suministrado.
   Objetivo: Revisar si el año suministrado es bisiesto.
   Retorno: (int) 1 si es bisiesto y 0 si no lo es.
*/
int isLeapYear(int year)
{
   return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

/*
Función: randrange.
Argumentos:
   int liminf: Límite inferior del rango aleatorio.
   int limsup: Límite superior del rango aleatorio.
Objetivo: Obtener número aleatorio en el rango: ['liminf','limsup'].
Retorno: (int) Equivalente al n�mero aleatorio obtenido.
*/
int randrange(int liminf, int limsup)
{
   return rand() % (limsup - liminf + 1) + liminf;
}
