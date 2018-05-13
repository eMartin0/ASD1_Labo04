//
//  LinkedList.cpp
//
//  Copyright (c) 2016 Olivier Cuisenaire. All rights reserved.
//

#include <iostream>
#include <stdexcept>

using namespace std;

/// Forward declaration classe
template < typename T > class LinkedList;

/// Forward declaration fonction d'affichage
template <typename T>
ostream& operator<<(ostream& os, const LinkedList<T>& liste);

/// Classe de liste chainee

template < typename T > class LinkedList {
   friend ostream& operator<< <T>(ostream& os, const LinkedList<T>& liste);
   //friend class Int;
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
   LinkedList() : nbElements(0), head(nullptr) {
   }

public:

   /**
    *  @brief Constructeur de copie
    *
    *  @param other la LinkedList à copier
    */
   LinkedList(LinkedList& other) : nbElements(0), head(nullptr) {
      *this = other;
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
      if (this != &other) {
         Node* currElement = head;
         size_t nbToDel = nbElements;
         size_t exc_safe = 0;

         if (other.size() > 0) {
            try {
               insert(other.head->data, nbElements);
               currElement = other.head->next;
               exc_safe++;

               while (currElement != nullptr) {
                  insert(currElement->data, nbElements);
                  currElement = currElement->next;
                  exc_safe++;
               }
            } catch (std::logic_error& e) {
               del(exc_safe);
               throw;
            }
         }

         for (size_t i = 0; i < nbToDel; i++) {
            pop_front();
         }
      }
      return *this;
   }

public:

   /**
    *  @brief destructeur
    */
   ~LinkedList() {
      while (nbElements) {
         pop_front();
      }
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
      ++nbElements;
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
      if (!nbElements) {
         throw runtime_error("La liste est vide.");
      }
      return head->data;
   }

   const_reference front() const { // O(1)
      if (!nbElements) {
         throw runtime_error("La liste est vide.");
      }
      return head->data;
   }

public:

   /**
    *  @brief Suppression de l'élément en tête de LinkedList
    *
    *  @exception std::runtime_error si la liste est vide
    */
   void pop_front() { // O(1)
      if (!nbElements) {
         throw runtime_error("La liste est vide.");
      }
      Node* tmp = head;
      head = head->next;
      delete tmp;
      --nbElements;
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
      if (pos > nbElements) {
         throw out_of_range("LinkedList::insert");
      } else if (pos == 0) {
         push_front(value);
      } else {
         Node* currElement = head;

         for (size_t i = 0; i < pos - 1; ++i) {
            currElement = currElement->next;
         }

         Node* newElement = new Node{value, currElement->next};
         currElement->next = newElement;
         ++nbElements;
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
      if (pos > nbElements - 1) {
         throw out_of_range("LinkedList::at");
      }
      Node* currElement = head;

      for (size_t i = 0; i < pos; ++i) {
         currElement = currElement->next;
      }
      return currElement->data;
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
      if (pos > nbElements - 1) {
         throw out_of_range("LinkedList::at");
      }
      const Node* currElement = head;

      for (size_t i = 0; i < pos; ++i) {
         currElement = currElement->next;
      }
      return currElement->data;
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
      if (pos > nbElements - 1) {
         throw out_of_range("LinkedList::erase");
      } else if (pos == 0) {
         pop_front();
      } else {
         Node* currElement = head;

         for (size_t i = 0; i < pos - 1; ++i) {
            currElement = currElement->next;
         }

         Node* nextElement = currElement->next;
         currElement->next = nextElement->next;
         delete nextElement;
         --nbElements;
      }
   }
   
private:
      
   void del(size_t pos) {
      while (pos) {
         erase(nbElements - pos);
         pos--;
      }
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
      size_t pos = 0;
      Node* currElement = head;

      for (int i = 0; i < nbElements; ++i) {
         if (currElement->data == value) {
            return pos;

         } else {
            pos++;
         }
         currElement = currElement->next;
      }

      return pos = -1;
   }

   /**
    *  @brief Tri des elements de la liste par tri fusion
    */

   void swapElements(Node*& a, Node*& b) {
      swap(a, b);
      swap(a->next, b->next);
   }

   Node*& merge(Node*& start, Node* middle, Node* end) {
      size_t pos = 0;
      while (start != middle) {
         if (start->data < middle->data) {
            swapElements(middle, start);
            start = start->next;
            pos++;
         } else {
            swapElements(start, middle);
            middle = middle->next;
            pos++;
         }

      }
      return start;
   }

   Node*& mergeSort(Node*& start, size_t nbElement) {
      if (nbElement > 0) {
         size_t middle = nbElements / 2;
         Node *half = head, *full = head;
         while (full && full->next) {
            half = half->next;
            full = full->next->next;
         }

         mergeSort(start, middle);
         mergeSort(half, nbElement);
         merge(start, half, full);
      }
      return start;

   }

   void sort() {
      mergeSort(head, nbElements);
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

class Int {
   int val;
public:

   Int() : val(0) {
   }

   Int(int i) : val(i) {
      if (i == -1) throw std::logic_error("Int::Constructor");
   }

   Int(const Int& i) : val(i.val) {
      if (i.val == -2) throw std::logic_error("Int::CopyConstructor");
   }

   Int& operator=(const Int& i) {
      if (i.val == -3) throw std::logic_error("Int::Operator=");
      val = i.val;
      cout << "(I=" << val << ") ";
      return *this;
   }

   bool operator<(const Int& i) {
      return val < i.val;
   }

   bool operator==(const Int& i) {
      return val == i.val;
   }

   friend ostream& operator<<(ostream& os, const Int& i);
};

ostream& operator<<(ostream& os, const Int& i) {
   os << i.val;
   return os;
}

using T = Int;

int main(int argc, const char * argv[]) {

   const int N = 9;

   cout << "Creation d'une liste de " << N << " entiers aléatoires \n";
   LinkedList<T> liste;
   for (unsigned i = 0; i < N; ++i) {
      liste.push_front(rand() % 100);
   }
   cout << "\n" << liste;

   cout << "\nModification de l'élément en tête à 42";
   liste.front() = 42;
   cout << "\n" << liste;

   cout << "\nModification de l'élément en position " << N / 2 << " à 43";
   liste.at(N / 2) = 43;
   cout << "\n" << liste;

   cout << "\nSuppression de l'élément en position " << N / 3 << "\n";
   liste.erase(N / 3);
   cout << "\n" << liste;

   cout << "\nSuppression de l'élément en dernière position \n";
   liste.erase(liste.size() - 1);
   cout << "\n" << liste;

   cout << "\nInsertion de l'élément 44 en position 0\n";
   liste.insert(44, 0);
   cout << "\n" << liste;

   cout << "\nInsertion de l'élément 45 en position " << N / 3 << "\n";
   liste.insert(45, N / 3);
   cout << "\n" << liste;

   cout << "\nInsertion de l'élément 46 en dernière position\n";
   liste.insert(46, liste.size());
   cout << "\n" << liste;

   cout << "\n\nRecherche d'elements allant de 0 à 99 \n";
   for (int i = 0; i < 100; ++i) {
      if (liste.find(i) != -1)
         cout << '(' << i << ')';
   }

   {
      cout << "\n\nCreation d'une copie constante de la liste\n";
      const LinkedList<T> copie = liste;
      cout << "\n" << copie.size() << ": ";
      for (size_t i = 0; i < copie.size(); ++i)
         cout << copie.at(i) << " ";
      cout << "\nDestruction de la copie constante\n";
   }

   {
      cout << "\n\nCreation d'une copie de la liste\n";
      LinkedList<T> copie = liste;
      cout << "\nCopie - " << copie;

      cout << "\nSuppression des " << N / 2 << " premiers éléments\n";
      for (int i = 0; i < N / 2; ++i)
         copie.pop_front();
      cout << "\nCopie - " << copie;

      cout << "\nRecopie de la liste original dans la copie\n";
      copie = liste;

      cout << "\nCopie - " << copie;
      cout << "\nDestruction de la copie\n";
   }

   try {
      cout << "\n\nInsertion hors de range";
      liste.insert(42, liste.size() + 1);
      cout << "\nException non levée";
   } catch (std::out_of_range& e) {
      cout << "\nstd::out_of_range capturée ";
   } catch (...) {
      cout << "\nPas la bonne exception";
   }

   try {
      cout << "\nSuppression hors de range";
      liste.erase(liste.size());
      cout << "\nException non levée";
   } catch (std::out_of_range& e) {
      cout << "\nstd::out_of_range capturée ";
   } catch (...) {
      cout << "\nPas la bonne exception";
   }

   try {
      cout << "\nAccès hors de range";
      liste.at(liste.size()) = 42;
      cout << "\nException non levée";
   } catch (std::out_of_range& e) {
      cout << "\nstd::out_of_range capturée ";
   } catch (...) {
      cout << "\nPas la bonne exception";
   }

   {
      cout << "\nCreation d'une liste vide";
      LinkedList<double> listeVide;
      try {
         cout << "\nAccès à l'élément de tête";
         listeVide.front() = 1;
         cout << "\nException non levée";
      } catch (std::runtime_error& e) {
         cout << "\nstd::runtime_error capturée ";
      } catch (...) {
         cout << "\nPas la bonne exception";
      }

      try {
         cout << "\nSuppression d'un élément";
         listeVide.pop_front();
         cout << "\nException non levée";
      } catch (std::runtime_error& e) {
         cout << "\nstd::runtime_error capturée ";
      } catch (...) {
         cout << "\nPas la bonne exception";
      }
   }

   try {
      cout << "\n\nInsertion avec exception à la copie";
      liste.push_front(-2);
   } catch (...) {
      cout << "\nException capturée";
      cout << "\n" << liste;
   }

   try {
      cout << "\n\nMise à -2 d'un élément de la liste (entraine une exception si il est copié) \n";
      liste.at(liste.size() / 2) = -2;
      cout << "\nCopie de liste avec exception à la copie d'un élément\n";
      LinkedList<T> copie = liste;
      cout << "\nException non levée ";
   } catch (...) {
      cout << "\nException capturée \n";
   }

   {
      cout << "\n\nPréparation d'une liste temporaire\n";
      LinkedList<T> copie;
      for (int i = 0; i < 5; ++i)
         copie.push_front(i);
      cout << "\n" << copie << "\n";

      try {
         cout << "\nAffectation de liste avec exception à la copie d'un élément\n";
         copie = liste;
         cout << "\nException non levée";
      } catch (...) {
         cout << "\nException capturée";
         cout << "\n" << copie << "\n";
         liste.at(liste.size() / 2) = 123;
      }
      cout << "\nDestruction de la liste temporaire\n";
   }

   cout << "\n\nTri fusion";
   cout << "\nAvant: " << liste;
   liste.sort();
   cout << "\nAprès: " << liste;

   cout << "\nDestruction liste \n";

   return EXIT_SUCCESS;
}