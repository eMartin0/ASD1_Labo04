//
//  LinkedList.cpp
//
//  Copyright (c) 2016 Olivier Cuisenaire. All rights reserved.
//

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

/// Forward declaration classe
template < typename T > class LinkedList;

/// Forward declaration fonction d'affichage
template <typename T>
ostream& operator<<(ostream& os, const LinkedList<T>& liste);

/// Classe de liste chainee

template < typename T > class LinkedList {
   friend ostream& operator<< <T>(ostream& os, const LinkedList<T>& liste);

public:
   using value_type = T;
   using reference = T&;
   using const_reference = const T&;
   using pointer = T*;
   using const_pointer = const T*;

private:

   /**
    *  @brief Maillon de la chaine.
    * 
    * contient une valeur et le lien vers le maillon suivant.
    */
   struct Node {
      value_type data;
      Node* next;

      Node(const_reference data, Node* next = nullptr)
      : data(data), next(next) {
         cout << "(C" << data << ") ";
      }
      Node(Node&) = delete;
      Node(Node&&) = delete;

      ~Node() {
         cout << "(D" << data << ") ";
      }
   };

private:
   /**
    *  @brief  Tete de la LinkedList
    */
   Node* head;

private:
   /**
    *  @brief Nombre d'éléments
    */
   size_t nbElements;

public:

   /**
    *  @brief Constructeur par défaut. Construit une LinkedList vide
    *
    */
   LinkedList() : nbElements(0), head(nullptr) { }

public:

   /**
    *  @brief Constructeur de copie
    *
    *  @param other la LinkedList à copier
    */
   LinkedList(LinkedList& other) /* ... */ {
      /* ... */
   }

public:

   /**
    *  @brief Opérateur d'affectation par copie
    *
    *  @param other la LinkedList à copier
    *
    *  @return la LinkedList courante *this (par référence)
    *
    *  @remark l'opérateur doit être une no-op si other 
    *  est la LinkedList courante.
    *
    *  @remark le contenu précédent de la LinkedList courante est 
    *  effacé.
    */
   LinkedList& operator=(const LinkedList& other) {
      /* ... */
      return *this;
   }

public:

   /**
    *  @brief destructeur
    */
   ~LinkedList() {
      
   }

public:

   /**
    *  @brief nombre d'éléments stockés dans la liste
    *
    *  @return nombre d'éléments. 
    */
   size_t size() const noexcept {
      return nbElements;
   }

public:

   /**
    *  @brief insertion d'une valeur dans un maillon en tête de liste
    *
    *  @param value la valeur à insérer
    *
    *  @exception std::bad_alloc si pas assez de mémoire, où toute autre
    * exception lancée par la constructeur de copie de value_type
    */
   void push_front(const_reference value) { // O(1)
      head = new Node{value, head};
      nbElements++;
   }

public:

   /**
    *  @brief accès (lecture/écriture) à la valeur en tête de LinkedList
    *
    *  @return référence à cette valeur
    *
    *  @exception std::runtime_error si la liste est vide
    */
   reference front() { // O(1)
      if(nbElements){
         return head->data; // head.data pas content : (*head).data ?
      }
   }

   const_reference front() const { // O(1)
      if(nbElements){
         return head->data;
      }
   }

public:

   /**
    *  @brief Suppression de l'élément en tête de LinkedList
    *
    *  @exception std::runtime_error si la liste est vide
    */
   void pop_front() { // O(1) - Pourquoi passer par tmp.. ?
      if(nbElements){
         Node* tmp = new Node{ head->data, head->next };
         head = head->next;
         delete tmp;
         --nbElements;
      }
   }

public:

   /**
    *  @brief Insertion en position quelconque
    *
    *  @param value la valeur à insérer
    *  @param pos   la position où insérer, 0 est la position en tete
    *
    *  @exception std::out_of_range("LinkedList::insert") si pos non valide
    *
    *  @exception std::bad_alloc si pas assez de mémoire, où toute autre exception lancée par la constructeur de copie de value_type
    */
   void insert(const_reference value, size_t pos) {
      // dépiler jusqu'à la position et stocker les valeurs, ajouter la
      // nouvelle valeur et rempiler les valeurs stockées
      if(pos < nbElements){   
         size_t taille = pos + 1;
         value_type copie[taille];
         for(size_t i = 0; i < taille; ++i){
            copie[i] = head->data;
            cout << "i : " << i << " - data : " << head->data << endl;
            this->pop_front();
         }
         this->push_front(value);
         for(size_t i = taille-1; i >= 0;--i){
            this->push_front(copie[i]);
         }
         
      }
   }

public:

   /**
    *  @brief Acces à l'element en position quelconque
    *
    *  @param pos la position, 0 est la position en tete
    * 
    *  @exception std::out_of_range("LinkedList::at") si pos non valide
    *
    *  @return une reference a l'element correspondant dans la liste
    */
   reference at(size_t pos) {
      value_type retour;
      if(pos < nbElements){   
         size_t taille = pos + 1;
         value_type copie[taille];
         for(size_t i = 0; i < taille; ++i){
            copie[i] = head->data;
            cout << "i : " << i << " - data : " << head->data << endl;
            this->pop_front();
         }
         retour = head->data;
         for(size_t i = taille-1; i >= 0;--i){
            this->push_front(copie[i]);
         }
      }
      return retour;
   }

   /**
    *  @brief Acces à l'element en position quelconque
    *
    *  @param pos la position, 0 est la position en tete
    *
    *  @exception std::out_of_range("LinkedList::at") si pos non valide
    *
    *  @return une const_reference a l'element correspondant dans la liste
    */
   const_reference at(size_t pos) const {
      /* ... */
   }

public:

   /**
    *  @brief Suppression en position quelconque
    *
    *  @param pos la position, 0 est la position en tete
    *
    *  @exception std::out_of_range("LinkedList::erase") si pos non valide
    */
   void erase(size_t pos) {
      /* ... */
   }

public:

   /**
    *  @brief Recherche du premier élément correspondant
       à une valeur donnée dans la liste
    *
    *  @param value la valeur à chercher
    *
    *  @return la position dans la liste. -1 si la valeur
       n'est pas trouvée
    */
   size_t find(const_reference value) const noexcept {
      /* ... */
   }

   /**
    *  @brief Tri des elements de la liste par tri fusion
    */
   void sort() {
      /* ... */
   }

};

template <typename T>
ostream& operator<<(ostream& os, const LinkedList<T>& liste) {
   os << liste.size() << ": ";
   auto n = liste.head;
   while (n) {
      os << n->data << " ";
      n = n->next;
   }
   return os;
}

int main() {

   const int N = 10;

   cout << "Creation d'une liste de " << N << " entiers aleatoires \n";
   LinkedList<int> liste;
   for (unsigned i = 0; i < N; ++i) {
      liste.push_front(rand() % 100);
   }
   cout << "\n" << liste;

   cout << "\nModification de l'element en tete a 42 \n";
   liste.front() = 42;
   cout << "\n" << liste;

   cout << "\nSuppression de l'element en tete\n";
   liste.pop_front();
   cout << "\n" << liste;
   
   /*cout << "\nModification de l'élément en position " << N / 2 << " à 24 \n";
   liste.at(N / 2) = 24;
   cout << "\n" << liste;*/

   /*cout << "\nSuppression de l'élément en position " << 2 * N / 3 << "\n";
   liste.erase(2 * N / 3);
   cout << "\n" << liste;

   cout << "\nInsertion de l'élément 421 en position 0\n";
   liste.insert(421, 0);
   cout << "\n" << liste;

   cout << "\nInsertion de l'élément 422 en position " << N / 3 << "\n";
   liste.insert(422, N / 3);
   cout << "\n" << liste;

   cout << "\nInsertion de l'élément 423 en dernière position\n";
   liste.insert(423, liste.size());
   cout << "\n" << liste;

   cout << "\nDestruction de la liste \n"; */


   return EXIT_SUCCESS;
}