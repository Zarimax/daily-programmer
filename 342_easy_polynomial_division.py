from itertools import izip

class Poly(object):
    def degree(self):
        return len(self.coeff) - 1
    
    def __init__(self, coefficients):
        self.coeff = coefficients
        while self.coeff and self.coeff[-1] == 0:
            self.coeff.pop() # remove meaningless high-order zero coefficients

    def __str__(self):
        s = ''
        for i in range(len(self.coeff)):
            s += ' + %g*x^%d' % (self.coeff[i], i)
        if (len(s) == 0):
            s = "0"
        return s

    def __div__(self, other):
        N = self.coeff      # numerator
        dN = self.degree()  # degree of the numerator
        
        D = other.coeff     # denominator
        dD = other.degree() # degree of the denominator

        if dD < 0: raise ZeroDivisionError
        if dN >= dD:
            q = [0] * dN
            while dN >= dD:
                d = [0]*(dN - dD) + D
                mult = q[dN - dD] = N[-1] / float(d[-1])
                d = [coeff*mult for coeff in d]
                N = [coeffN - coeffd for coeffN, coeffd in izip(N, d)]
                while N and N[-1] == 0:
                    N.pop()   # remove meaningless high-order zero coefficients
                dN = len(N) - 1
            r = N
        else:
            q = [0]
            r = N
        return Poly(q), Poly(r)
        
if __name__ == '__main__':
    p1 = Poly([3, -6, 2, 4])
    p2 = Poly([-3, 1])
    print "  %s / %s =" % (p1, p2),
    print " %s remainder %s" % (p1 / p2)

    p1 = Poly([12, -26, 21, -9, 2])
    p2 = Poly([-3, 2])
    print "  %s / %s =" % (p1, p2),
    print " %s remainder %s" % (p1 / p2)

    p1 = Poly([-1, 0, -7, 0, 10])
    p2 = Poly([3, -1, 1])
    print "  %s / %s =" % (p1, p2),
    print " %s remainder %s" % (p1 / p2)
