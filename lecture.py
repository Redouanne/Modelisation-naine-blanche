import pandas as pd
import numpy as np

#Importation and creation of the different dataset =============================================
data_full=pd.read_csv('C:/Users/Victor/Desktop/C++/Codes/Pantheon+SH0ES.dat', sep = " ")
data_single_survey = data_full.drop_duplicates(subset = ["RA"], keep = 'first') #Dataset without duplicated SNe1a according to RA parameter
main_parameters = ["zCMB","mB","x1","c","IDSURVEY","zHEL","RA","DEC","VPEC"]
uncertainty_parameters = ["cERR", "x1ERR", "mBERR", "COV_x1_c", "COV_x1_x0", "COV_c_x0"]
data_main = data_single_survey[main_parameters + uncertainty_parameters] #Dataset which contains the usefull parameters for the analyses
data_main_RAsorted = data_main.sort_values(by="RA",ascending = True) #Dataset sorted according ro RA used for cuts
#===============================================================================================

data_main_RAsorted.to_csv('data/data.csv',index = False, header = False)
