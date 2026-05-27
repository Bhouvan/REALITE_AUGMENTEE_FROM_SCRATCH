#include "Float.h"
 


 namespace NkMath {
    
        // Sommation de Kahan — O(N) comme std::accumulate mais BEAUCOUP plus précis 
        double kahanSum(const double* data, int n) { 
            double sum  = 0.0; 
            double comp = 0.0;  // compensation des erreurs perdues 
        
            for(int i = 0; i < n; i++) { 
                double y = data[i] - comp;    // compenser l'erreur précédente 
                double t = sum + y;           // t est grand, y est petit → perte de bits 
                comp    = (t - sum) - y;     // capture les bits perdus dans y 
                sum     = t; 
            } 
            return sum;
        }
        
        double sommeNaive(const double* data, int n){
            
            return std::accumulate(data, data + n, 0.0);
        }
        void RemplirTab(double* data,int n,double value){
            for(int i= 0;i<n;i++)
                data[i]=value;           
        }
    } // namespace NKMath
