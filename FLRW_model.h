/*
Cette classe définit le modèle cosmologique étudié. Dans notre projet, nous nous sommes limités
au FLRW model, utilisant la matière baryonique, l'énergie du vide ainsi que la courbure de
l'espace temps pour calculer les distances. Un objet de cette classe correspond donc à un univers avec
différents paramètres cosmologiques.

La distance luminosité dL est premièrement calculée à partir de l'équation de Friedmann. Cette dernière
permet ensuite de remonter à la distance modulus théorique, qui sera par la suite comparée avec celle
obtenue expérimentalement.
*/

class FLRW {
    private:
        double om0, oml, c, dH;
    
    public:
        FLRW(double om0, double oml, double H0 = 66.7); // om0 : Matière baryonique, oml : énergie du vide
    
        double omk() const; //terme de courbure de l'espace temps : omk = 1 - omt (avec omt = om0 + oml) => om0 + oml + omk = 1
    
        static double integrand(double z, void* params); //calcul de l'intégrant pour la distance luminosité
        double integrate(double z);
        double dL(double z);
    
        double mu(double z);
    };