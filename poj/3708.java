import java.math.BigInteger;
import java.util.Scanner;



public class Main {
	
	static final int N = 1000;
	static int[] a = new int[N];
	static int[] b = new int[N];
	static int[] nn = new int[N];
	static int[] kk = new int[N];
	static boolean[] vis = new boolean[N];
	static int[] c1 = new int[N];
	static int[] c2 = new int[N];
	static BigInteger[] r = new BigInteger[N];
	static BigInteger[] m = new BigInteger[N];
	
	
	static int getC1(int cnt1, int d) {
		for (int i = 0; i < cnt1 - 1; i++)	{
			int tmp = nn[i];
			c1[i] = -1;
			for (int j = 0; j <= d; j++) 
			if (tmp == kk[i]){
				c1[i] = j;
				break;
			}
			else tmp = b[tmp];
			if (c1[i] == -1) return -1;
		}
		
		int tmp = nn[cnt1-1];
		c1[cnt1-1] = -1;
		for (int j = 0; j <= d; j++) 
		if (tmp == kk[cnt1-1]){
			c1[cnt1-1] = j;
			break;
		}
		else tmp = a[tmp];
		if (c1[cnt1-1] == -1) return -1;		
		return 0;
	}
	
	static int getC2(int cnt1, int d) {
		for (int i = 0; i < cnt1 - 1; i++) {
			int tmp = b[kk[i]];
			c2[i] = -1;
			for (int j = 0; j <= d; j++) {
				if (tmp == kk[i]) {
					c2[i] = j + 1;
					break;
				}
				tmp = b[tmp];
			}
			if (c2[i] == -1) return -1;
		}
		int tmp = a[kk[cnt1-1]];
		c2[cnt1-1] = -1;
		for (int j = 0; j <= d; j++) {
			if (tmp == kk[cnt1-1]) {
				c2[cnt1-1] = j + 1;
				break;
			}
			tmp = a[tmp];
		}
		if (c2[cnt1-1] == -1) return -1;
		return 0;
	}
	
	static BigInteger x, y, z;
	static void ex_gcd(BigInteger a, BigInteger b) {
		if (b.equals(BigInteger.ZERO)) {
			x = BigInteger.ONE;
			y = BigInteger.ZERO;
			z = a;
			return;
		}
		ex_gcd(b, a.mod(b));
		BigInteger tmp = x;
		x = y;
		y = tmp.subtract(a.divide(b).multiply(x));
	}
	
	static long ex_crt(BigInteger[] r, BigInteger[] m, int n) {
		BigInteger M = m[0], R = r[0];
		for (int i = 1; i < n; i++) {
			ex_gcd(M, m[i]);
			if (!(r[i].subtract(R)).mod(z).equals(BigInteger.ZERO)) return -1;
			x = x.multiply((r[i].subtract(R)).divide(z)).mod(m[i].divide(z));
			R = R.add(M.multiply(x));
			M = M.divide(z).multiply(m[i]);
			R = R.mod(M);
		}
		if (R.compareTo(BigInteger.ZERO) >= 0) return R.longValue();
		return R.add(M).longValue();
	}
	
	
	public static void main(String[] args) {
//		ex_gcd(BigInteger.valueOf(3), BigInteger.valueOf(5));
//		System.out.print(x+" "+y);
		Scanner in = new Scanner(System.in);
		while (in.hasNext()) {
			int d = in.nextInt();
			if (d == -1) break;
			BigInteger dd = BigInteger.valueOf(d);
			for (int i = 1; i < d; i++) a[i] = in.nextInt();
			for (int i = 0; i < d; i++) b[i] = in.nextInt();
			BigInteger n = in.nextBigInteger();
			BigInteger k = in.nextBigInteger();
			int cnt1 = 0, cnt2 = 0;
			while (!n.equals(BigInteger.ZERO)) {
				nn[cnt1++] = n.mod(dd).intValue();
				n = n.divide(dd);
			}
//			for (int i = 0; i < cnt1; i++)
//				System.out.print(nn[i]);
//			System.out.println();
			while (!k.equals(BigInteger.ZERO)) {
				kk[cnt2++] = k.mod(dd).intValue();
				k = k.divide(dd);
			}
//			for (int i = 0; i < cnt2; i++)
//				System.out.print(kk[i]);
//			System.out.println();
			if (cnt1 != cnt2) {
				System.out.println("NO");
				continue;
			}
			
			if (getC1(cnt1, d) == -1 || getC2(cnt1, d) == -1) {
				System.out.println("NO");
				continue;
			}
//			for (int i = 0; i < cnt1; i++)
//				System.out.print(c1[i]+ " ");
//			System.out.println();
//			for (int i = 0; i < cnt1; i++)
//				System.out.print(c2[i]+ " ");
//			System.out.println();
			for (int i = 0; i < cnt1; i++) {
				r[i] = BigInteger.valueOf(c1[i]);
				m[i] = BigInteger.valueOf(c2[i]);
			}
			
			long ret = ex_crt(r, m, cnt1);
			if (ret == -1) 	System.out.println("NO");
			else System.out.println(ret);
 		}
	}
}

