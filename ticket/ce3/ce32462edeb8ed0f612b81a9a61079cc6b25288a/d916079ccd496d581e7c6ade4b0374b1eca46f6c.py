#!/usr/bin/python2.4


def GetCMYK(rgb):
	import decimal
	D=decimal.Decimal
	(r,g,b)=rgb
	C=D(1)-(D(r)/D(255))
	M=D(1)-(D(g)/D(255))
	Y=D(1)-(D(b)/D(255))
	if min(C,M,Y)==D(1):
		CMYK=(0,0,0,1)
	else:
		K=min(C,M,Y)
		C=int(D(((D(C)-D(K))/(D(1)-D(K)))*D(255)).quantize(D(0)))
		M=int(D(((D(M)-D(K))/(1-D(K)))*D(255)).quantize(D(0)))
		Y=int(D(((D(Y)-D(K))/(1-D(K)))*D(255)).quantize(D(0)))
		if K < 0:
			K=0
		K=int((D(K)*D(255)).quantize(D(0)))
		CMYK=(C,M,Y,K)
	return CMYK


if __name__=="__main__":
	rgb=(93,63,88)
	cmyk=GetCMYK(rgb)
	if cmyk[3] > 100:
		print "TO DARK"
	else:
		print "yee haw"
 	  	 
