package com.example.jnidemo;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    public native String helloFromJNI();
    public native int factorial(int n);
    public native String reverseString(String s);
    public native int sumArray(int[] valeurs);

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tvHello   = findViewById(R.id.tvHello);
        TextView tvFact    = findViewById(R.id.tvFact);
        TextView tvReverse = findViewById(R.id.tvReverse);
        TextView tvArray   = findViewById(R.id.tvArray);
        TextView tvTests   = findViewById(R.id.tvTests);

        // Démonstration principale
        tvHello.setText(helloFromJNI());

        int resultFactoriel = factorial(10);
        tvFact.setText("10! = " + resultFactoriel);

        String texteInverse = reverseString("JNI est puissant !");
        tvReverse.setText("Inversé : " + texteInverse);

        int[] monTableau = {10, 20, 30, 40, 50};
        tvArray.setText("Somme de {10,20,30,40,50} = " + sumArray(monTableau));

        // --- Tests guidés étape 10 ---
        StringBuilder tests = new StringBuilder();

        // Test 1 : valeur normale
        tests.append("Test 1 - factorial(10) = ")
                .append(factorial(10))
                .append("\n\n");

        // Test 2 : valeur négative → doit retourner -1
        tests.append("Test 2 - factorial(-5) = ")
                .append(factorial(-5))
                .append(" (attendu : -1)\n\n");

        // Test 3 : dépassement → doit retourner -2
        tests.append("Test 3 - factorial(20) = ")
                .append(factorial(20))
                .append(" (attendu : -2)\n\n");

        // Test 4 : chaîne vide → doit retourner ""
        String resultVide = reverseString("");
        tests.append("Test 4 - reverseString(\"\") = \"")
                .append(resultVide)
                .append("\" (attendu : vide)\n\n");

        // Test 5 : tableau vide → doit retourner 0
        tests.append("Test 5 - sumArray({}) = ")
                .append(sumArray(new int[]{}))
                .append(" (attendu : 0)");

        tvTests.setText(tests.toString());
    }
}