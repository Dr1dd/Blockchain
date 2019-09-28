# 1-oji užduotis: Hash generatorius
Maišos funkcijos (angl. *hash function*) yra labai svarbi *blockchain* (pvz. *Bitcoin*) protokolų dalis. Hash'avimo metu bet koks įvedimo tekstas (*m*) matematinės *hash* funkcijos dėka (*h = h(m)*) yra paverčiamas unikaliu fiksuoto dydžio pseudo-atsitiktiniu skaičiumi, vadinamu *maišos kodu*.

## Ko jums reikės paleisti programą:

Cmake įrangos įrankio.

Rekomenduojami IDE:

Visual Studio ar JetBrains Clion

## (v0.1) versija:
### 1. Susikurkite testinių įvedimo failų pavyzdžių, tokių kad:
  - **Bent du failai būtų sudaryti tik iš vieno, tačiau skirtingo, simbolio.**
  
  **Failas 1:**
  
  ![pic](https://imgur.com/hQAVK4G.png)
  
  **Failas 2:**
  
  ![pic](https://imgur.com/WDMRlYf.png)
  
  
  
  - **Bent du failai būtų sudaryti iš daug visiškai skirtingų simbolių (> 10000 simbolių)**
  
  **Failas 1:**
  
  ![pic](https://imgur.com/dlBdeFP.png)
  
  **Failas 2:**
  
  ![pic](https://imgur.com/NGXSMYn.png)
  
  
  
  
  - **Bent du failai būtų sudaryti iš daug simbolių ir skirtųsi vienas nuo kito tik vienu simboliu.**
  
  **Failas 1:**
  
  ```
TZLI89e5Y7rwaBsOJ1S3VS3Y0RgjOcGtchUYN51FS3jdFH3vzB3TokL3UP90xlRGBqynxJCWDcgHcipjRBH8UeC4whtreFStuem7aWcq6d1MLmtBXnzkwUSjQnaiyzchHxNK3wAhEE0cuqfFDGdXLQNf8tXsaQ3vZzCm5FWkEC3qPn0qdNuYrxL4VczCQneyY2KhqZ5uFqxJRS7asVkcf2h5vQaY87XWfZJHyMtjRrIcvCREkDcTOwXbCwOTQsvtjPakJPplfOMqehcBZ08rCRr13Jj0gKLHrZ6eIz0gWfFb4iCoz373Wb3BQoKZTztVrd859tkSbswkx216Z73Ch0P4VNhAkYtlkWgv7gTAjzVEg6lE9clGIn2pAHNhQvhdFgFlP63LQHbw2uMYCQsco6wI7hiGuDPbTRllgsY7c64WdEepZEsmFIt8EQPk47B04f62zew9FJfqV007bkKbCSCQUSIp8LmIWTLRyKA7vvCjCAQZBLDJLXGNbJr0104rJKYxK9fz2ihl8sCf41xkH98Wo8uMUB4g58yoxLVnpcl6j1uD3G82OFzf9rZQkBa1XnIeuw7o1XsK1P7k2hGiXStIBV4qqoCca0EOOLdPq5DzFYP3Qu6sUXoUEPSi2F1EUwF7ccX0wPdaYRYQcv41VZXNhEnlVO1ouPhZh7h07nrzDwvFxSp9xjBbirKujL5GfQXfLQatiFMcc0pqznnMN9AIoHnHEmnztAFNsOPUrYCTI8aPMlYhUOQTwesQ0m5WeX2QsR6LTXshfROoSUQlbdZG6J5GFcEMUayUvjkHlnbjKTQcXFbJ9GIXtNt3grfBHZa8xxT3oJ7QdDvAqhOCAI494ZCpXyt9tNiANZsEPHBpZOXfxekBNns8FKfI30eAXs5YxIlbYNHPVpFnU3gdqOxjZu7hv9ZKxSIWUfgBaFl96gAqsDd2XpKP9XMB1WlpyPpmbs2hty1SSGmvoK1PPxho8GmJqg7QogeDan54
  ```
  
  ![pic](https://imgur.com/qi6gLj7.png)
  
  **Failas 2:**
  
  ```
  TZLI89e5Y7rwaBsOJ1S3VS3Y0RgjOcGtchUYN51FS3jdFH3vzB3TokL3UP90xlRGBqynxJCWDcgHcipjRBH8UeC4whtreFStuem7aWcq6d1MLmtBXnzkwUSjQnaiyzchHxNK3wAhEE0cuqfFDGdXLQNf8tXsaQ3vZzCm5FWkEC3qPn0qdNuYrxL4VczCQneyY2KhqZ5uFqxJRS7asVkcf2h5vQaY87XWfZJHyMtjRrIcvCREkDcTOwXbCwOTQsvtjPakJPplfOMqehcBZ08rCRr13Jj0gKLHrZ6eIz0gWfFb4iCoz373Wb3BQoKZTztVrd859tkSbswkx216Z73Ch0P4VNhAkYtlkWgv7gTAjzVEg6lE9clGIn2pAHNhQvhdFgFlP63LQHbw2uMYCQsco6wI7hiGuDPbTRllgsY7c64WdEepZEsmFIt8EQPk47B04f62zew9FJfqV007bkKbCSCQUSIp8LmIWTLRyKA7vvCjCAQZBLDJLXGNbJr0104rJKYxK9fz2ihl8sCf41xkH98Wo8uMUB4g58yoxLVnpcl6j1uD3G82OFzf9rZQkBa1XnIeuw7o1XsK1P7k2hGiXStIBV4qqoCca0EOOLdPq5DzFYP3Qu6sUXoUEPSi2F1EUwF7ccX0wPdaYRYQcv41VZXNhEnlVO1ouPhZh7h07nrzDwvFxSp9xjBbirKujL5GfQXfLQatiFMcc0pqznnMN9AIoHnHEmnztAFNsOPUrYCTI8aPMlYhUOQTwesQ0m5WeX2QsR6LTXshfROoSUQlbdZG6J5GFcEMUayUvjkHlnbjKTQcXFbJ9GIXtNt3grfBHZa8xxT3oJ7QdDvAqhOCAI494ZCpXyt9tNiANZsEPHBpZOXfxekBNns8FKfI30eAXs5YxIlbYNHPVpFnU3gdqOxjZu7hv9ZKxSIWUfgBaFl96gAqsDd2XpKP9XMB1WlpyPpmbs2hty1SSGmvoK1PPxho8GmJqg7QogeDan57

  ```
  
  ![pic](https://imgur.com/GK2SOai.png)
  
  Skirtumas:
  
  ![pic](https://imgur.com/y4Z9CqC.png)
  
  - **Tuščias failas**
**Ir išveskite output'us. Nepriklausomai nuo Input'o, Output'ai turi būti vienodo dydžio. Tokiu būdu pademonstruosite, kad Jūsų _hash funkcija_ atitinka 1-3-ą reikalavimus.**



### 2. Ištirkite Jūsų sukurtos hash funkcijos efektyvumą: tuo tikslu suhash'uokite kiekvieną eilutę iš konstitucija.txt failo. Reiktų čia matuoti, tik hash'avimo funkcijos veikimo laiką (be input'o nuskaitymo/parengimo). Reiktų pateikti bendrą suminį visų hash'avimų laiką.

  ![pic](https://imgur.com/uV0nMgv.png)
  
  Pavyzdys:
  
  ![pic](https://imgur.com/D7BAnX0.png)
  
### 3. Susigeneruokite bent 1000 000 atsitiktinių simbolių eilučių (string'ų) porų, pvz.: (asdfg, hijkl) apsiribojant iki 5 simbolių eilučių ilgiu ir patikrinkite, kad visais atvejais gautieji porų hash'ai nesutampa. 
Pavyzdžiai:

 [Generuotas Tekstas](https://github.com/Dr1dd/Blockchain/blob/dev/randomText/3uzdGeneruotasTekstas.txt)
 
 [Hashuotas Tekstas](https://github.com/Dr1dd/Blockchain/blob/dev/randomText/3uzdRezultatas.txt)
 
 Tikrinimo kodas:
 
 ```
 		int sutampa = 0;
    cout << "Rezultatai sugeneruoti. Pradedamas hash'u lyginimas" << endl;
	for(int j =0; j<2222222; j++){
	    if(j%2!=0){
            if(genvector[j] == genvector[j-1]){
                cout << "sutampa = " << genvector[j] << " " << j/2 << " eilute" << endl;
                sutampa++;
            }
	    }
	}
	cout<< "Sutapimu = " << sutampa << endl;
  ```
  
  Rezultatas:
  
  ![img](https://imgur.com/Ochd1nk.png)
  
  
  ### 4. Susigeneruokite bent 100 000 atsitiktinių simbolių eilučių (string'ų) porų, , pvz.: (asdfg, bsdfg) tokių kad skirtųsi jos tik vienu simboliu ir apsiribojant iki 5 simbolių eilučių ilgiu. Įvertinkite Jūsų gautų hash'ų procentinį "skirtingumą" bitų lygmenyje. Išveskite minimalią, maksimalią ir vidurkines "skirtingumo" reikšmes. Tokiu būdų įsitikinsite, kaip gerai Jūsų hash funkcija atitinka 7-ą reikalavimą.
  
 Sugeneruojamos 100000 porų -> kiekvienas poros dalyvis užhash'uojamas -> kiekvienas užhashuotas poros dalyvis paverčiamas į dvejetainę.

![pic](https://imgur.com/DPXF1d9.png)

Rezultatai:

Tikrinamas kiekvienas skaičius su atitinkamu poros dalyvio skaičiumi. Randami atitikimai = prie kintamojo pridedamas +1.

Suskaičiuojami ```min```, ```max```, ```average``` skirtumai tarp porų bitų lygyje.

![pic](https://imgur.com/wGY6aDE.png)
