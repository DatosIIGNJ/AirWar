package com.example.juand.control11;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ConnectActivity extends AppCompatActivity {
    Button btnConect;
    ImageButton btnFire,btnLeft,btnUp,btnRight,btnDown;
    DataOutputStream salida;
    DataInputStream entrada;
    Socket cliente;
    EditText txtIP,txtPlayer;
    TextView txtNomPlay;
    String msjServer = null;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_connect);
        btnConect=(Button)findViewById(R.id.btnConect);
        txtPlayer=(EditText)findViewById(R.id.txtPlayer);
        txtIP=(EditText)findViewById(R.id.txtIP);
        btnFire=(ImageButton)findViewById(R.id.btnFire);
        btnLeft=(ImageButton)findViewById(R.id.btnleft);
        btnUp=(ImageButton)findViewById(R.id.btnup);
        btnDown=(ImageButton)findViewById(R.id.btndown);
        btnRight=(ImageButton)findViewById(R.id.btnright);
        txtNomPlay=(TextView)findViewById(R.id.txtPlayerN);
        btnConect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Thread t = new Thread() {
                    public void run() {
                        try {
                            cliente = new Socket(txtIP.getText().toString(), 8081);
                            salida = new DataOutputStream(cliente.getOutputStream());
                            entrada = new DataInputStream(cliente.getInputStream());
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                };
                t.start();
                btnFire.setVisibility(View.VISIBLE);
                btnLeft.setVisibility(View.VISIBLE);
                btnUp.setVisibility(View.VISIBLE);
                btnRight.setVisibility(View.VISIBLE);
                btnDown.setVisibility(View.VISIBLE);
                txtIP.setVisibility(View.INVISIBLE);
                txtPlayer.setVisibility(View.INVISIBLE);
                btnConect.setVisibility(View.INVISIBLE);
                txtNomPlay.setText("Player: "+txtPlayer.getText());
                txtNomPlay.setVisibility(View.VISIBLE);
            }
        });
        btnFire.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    salida.writeUTF("Fire");
                    salida.flush();
                    //Readerm readmsj = new Readerm(entrada);
                    //readmsj.start();
                    //while (msjServer == null){
                    //  msjServer = readmsj.readMessage();
                    //}

                } catch (IOException e) {
                    e.printStackTrace();
                }
                msjServer=null;
            }
        });
        btnLeft.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    salida.writeUTF("Left");
                    salida.flush();
                    //Readerm readmsj = new Readerm(entrada);
                    //readmsj.start();
                    //while (msjServer == null){
                    //  msjServer = readmsj.readMessage();
                    //}

                } catch (IOException e) {
                    e.printStackTrace();
                }
                msjServer=null;
            }
        });
        btnRight.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    salida.writeUTF("Right");
                    salida.flush();
                    //Readerm readmsj = new Readerm(entrada);
                    //readmsj.start();
                    //while (msjServer == null){
                    //  msjServer = readmsj.readMessage();
                    //}

                } catch (IOException e) {
                    e.printStackTrace();
                }
                msjServer=null;
            }
        });
        btnDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    salida.writeUTF("Down");
                    salida.flush();
                    //Readerm readmsj = new Readerm(entrada);
                    //readmsj.start();
                    //while (msjServer == null){
                    //  msjServer = readmsj.readMessage();
                    //}

                } catch (IOException e) {
                    e.printStackTrace();
                }
                msjServer=null;
            }
        });
        btnUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    salida.writeUTF("Up");
                    salida.flush();
                    //Readerm readmsj = new Readerm(entrada);
                    //readmsj.start();
                    //while (msjServer == null){
                    //  msjServer = readmsj.readMessage();
                    //}

                } catch (IOException e) {
                    e.printStackTrace();
                }
                msjServer=null;
            }
        });
    }
}
