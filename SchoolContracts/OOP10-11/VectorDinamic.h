#pragma once
//#include "domain.h"


//typedef Subject Element;

template <typename ElementT>
class IteratorVector;

template <typename ElementT>
class VectorDinamic {
	/*
	Constructor default
	Alocam loc pentru 5 elemente
	*/
public:
	VectorDinamic();

	/*
	Constructor de copiere
	*/
	VectorDinamic(const VectorDinamic& ot); //rule of 3

	/*
	Eliberam memoria
	*/
	~VectorDinamic();//rule of 3

	/*
	  Operator assgnment
	  elibereaza ce era in obiectul curent (this)
	  aloca spatiu pentru elemente
	  copieaza elementele din ot in this
	*/
	VectorDinamic& operator=(const VectorDinamic& ot);//rule of 3


	/*
	 Move constructor
	 Apelat daca construim un nou vector dintr-un r-value (ex temporary, expresie de la return)
	 Obiectul ot nu se mai foloseste astfel se poate refolosi interiorul lui
	*/
	VectorDinamic(VectorDinamic&& ot); //rule of 5 

	/*
	Move assignment
	Similar cu move constructor
	Folosit la assignment
	*/
	VectorDinamic& operator=(VectorDinamic&& ot); //rule of 5 


	void add(const ElementT& el); 
	void del(ElementT& poz);

	ElementT& get(int poz) const;

	void set(int poz, const ElementT& el);

	int size() const noexcept;
	friend class IteratorVector<ElementT>;
	IteratorVector<ElementT> begin();
	IteratorVector<ElementT> end();
private:
	int lg;
	int cp;
	ElementT* elems;
	void EnsureCapacity();
};

template <typename ElementT>
class IteratorVector {
private:
	const VectorDinamic<ElementT>& v;
	int poz = 0;
public:
	IteratorVector(const VectorDinamic<ElementT>& v) noexcept;
	IteratorVector(const VectorDinamic<ElementT>& v, int poz) noexcept;
	bool valid() const noexcept;
	ElementT& element() noexcept;
	void next() noexcept;
	ElementT& operator*();
	IteratorVector& operator++();
	bool operator==(const IteratorVector& ot) noexcept;
	bool operator!=(const IteratorVector& ot) noexcept;
};

template<typename ElementT>
VectorDinamic<ElementT>::VectorDinamic() : elems{ new ElementT[5] }, cp{ 1 }, lg{ 0 }{}

template<typename ElementT>
VectorDinamic<ElementT>::VectorDinamic(const VectorDinamic& ot)
{
	elems = new ElementT[ot.cp];
	for (int i = 0; i < ot.lg; i++) {
		elems[i] = ot.elems[i];
	}
	lg = ot.lg;
	cp = ot.cp;
}
template<typename ElementT>
VectorDinamic<ElementT>::~VectorDinamic()
{
	delete[] elems;
}
template<typename ElementT>
VectorDinamic<ElementT>& VectorDinamic<ElementT>::operator=(const VectorDinamic<ElementT>& ot)
{
	if (this == &ot) {
		return *this;
	}
	delete[] elems;
	elems = new ElementT[ot.cp];
	for (int i = 0; i < ot.lg; i++) {
		elems[i] = ot.elems[i];
	}
	lg = ot.lg;
	cp = ot.cp;
	return *this;
}
template<typename ElementT>
VectorDinamic<ElementT>::VectorDinamic(VectorDinamic&& ot)
{
	elems = ot.elems;
	lg = ot.lg;
	cp = ot.cp;

	ot.elems = nullptr;
	ot.lg = 0;
	ot.cp = 0;

}
template<typename ElementT>
VectorDinamic<ElementT>& VectorDinamic<ElementT>::operator=(VectorDinamic&& ot)
{
	if (this == &ot) {
		return *this;
	}
	delete[] elems;
	elems = ot.elems;
	lg = ot.lg;
	cp = ot.cp;
}
template<typename ElementT>
void VectorDinamic<ElementT>::add(const ElementT& el)
{
	EnsureCapacity();
	elems[lg++] = el;
}
template<typename ElementT>
void VectorDinamic<ElementT>::del(ElementT& it)
{
	for (int i = 0; i < lg; i++) {
		if (elems[i] == it) {
			for (int j = i; j < lg; j++)
			{
				elems[i] = elems[i + 1];
			}
			
		}
	}
	lg--;
}

template<typename ElementT>
ElementT& VectorDinamic<ElementT>::get(int poz) const
{
	return elems[poz];
}

template<typename ElementT>
void VectorDinamic<ElementT>::set(int poz, const ElementT& el)
{
	elems[poz] = el;
}

template<typename ElementT>
int VectorDinamic<ElementT>::size() const noexcept
{
	return lg;
}

template<typename ElementT>
void VectorDinamic<ElementT>::EnsureCapacity()
{
	if (lg < cp) { return; }

	cp *= 2;
	ElementT* aux = new ElementT[cp];
	for (int i = 0; i < lg; i++) {
		aux[i] = elems[i];

	}
	delete[] elems;
	elems = aux;
}

template<typename ElementT>
IteratorVector<ElementT> VectorDinamic<ElementT>::begin()
{
	return IteratorVector<ElementT>(*this);
}

template<typename ElementT>
IteratorVector<ElementT> VectorDinamic<ElementT>::end()
{
	return IteratorVector<ElementT>(*this, lg);
}


template<typename ElementT>
IteratorVector<ElementT>::IteratorVector(const VectorDinamic<ElementT>& v) noexcept :v{ v }
{
}

template<typename ElementT>
IteratorVector<ElementT>::IteratorVector(const VectorDinamic<ElementT>& v, int poz) noexcept :v{ v }, poz{ poz }
{
}

template<typename ElementT>
bool IteratorVector<ElementT>::valid() const noexcept
{
	return poz < v.lg;
}

template<typename ElementT>
ElementT& IteratorVector<ElementT>::element() noexcept
{
	return v.elems[poz];
}

template<typename ElementT>
void IteratorVector<ElementT>::next() noexcept
{
	poz++;
}

template<typename ElementT>
ElementT& IteratorVector<ElementT>::operator*()
{
	return element();
}

template<typename ElementT>
IteratorVector<ElementT>& IteratorVector<ElementT>::operator++()
{
	next();
	return *this;
}

template<typename ElementT>
bool IteratorVector<ElementT>::operator==(const IteratorVector<ElementT>& ot) noexcept
{
	return poz == ot.poz;
}

template<typename ElementT>
bool IteratorVector<ElementT>::operator!=(const IteratorVector<ElementT>& ot) noexcept
{
	return !(*this == ot);
}