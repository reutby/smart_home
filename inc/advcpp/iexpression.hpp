#ifndef IEXPRESSION_H
#define IEXPRESSION_H

namespace experis{

class IExpression{
public:
    virtual ~IExpression(){};
    virtual bool CheackEexpression() = 0;

};

template<class Classname>
class MemFuncExpression : public IExpression{
public:
    typedef bool (Classname::*ExpressionFunc)()const;
    MemFuncExpression(Classname& a_class,ExpressionFunc a_expressionfunc);
    bool CheackEexpression();
private:
    Classname& m_class;
    ExpressionFunc m_expression;

};

template<class Classname>
MemFuncExpression<Classname>::MemFuncExpression(Classname& a_class,ExpressionFunc a_expressionfunc)
: m_class(a_class)
, m_expression(a_expressionfunc)
{
}
template<class Classname>
bool MemFuncExpression<Classname>::CheackEexpression()
{
    return (m_class.*m_expression)();
}

}//experis

#endif//IEXPRESSION_H