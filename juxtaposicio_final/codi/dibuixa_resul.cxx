/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: Cone.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
//
// This example creates a polygonal model of a cone, and then renders it to
// the screen. It will rotate the cone 360 degrees and then exit. The basic
// setup of source -> mapper -> actor -> renderer -> renderwindow is
// typical of most VTK programs.
//

// First include the required header files for the VTK classes we are using.
#include <vtkSmartPointer.h>
#include <vtkPolygon.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAppendPolyData.h>

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkWindowToImageFilter.h"
#include "vtkPNGWriter.h"

#include "vtkCamera.h"



#include <vtkPolyDataMapper2D.h>
#include <vtkActor2D.h>
#include <vtkMath.h>
#include <vtkProperty2D.h>


#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>

#include <vtkProperty.h>
#include <vtkActor.h>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>



#define WSIZE 420

using namespace std;

int main(int argc, char *argv[]) {
	int RGB2[3], RGB1[3];
    char auxi[128];
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int num3 = atoi(argv[3]);
    int num4 = atoi(argv[4]);



    vector<float> v_x;
    vector<float> v_y;
    vector<float> v2_x;
    vector<float> v2_y;



    ifstream fe("vertex1.txt");
    char cadena[128];
    // Leeremos mediante getline, si lo hiciéramos
    // mediante el operador >> sólo leeríamos
    // parte de la cadena:
    fe.getline(cadena, 128);


    int n_ver1 = atoi(cadena);

    for (int aux = 0; aux < n_ver1; aux++) {
        char aux_x[128], aux_y[128];
        fe.getline(aux_x, 128);
        v_x.push_back(atoi(aux_x));
        fe.getline(aux_y, 128);
        v_y.push_back(atoi(aux_y));


    }
	fe.getline(auxi, 128);
        
    RGB1[0]=atoi(auxi);
fe.getline(auxi, 128);
        
    RGB1[1]=atoi(auxi);
fe.getline(auxi, 128);
        
    RGB1[2]=atoi(auxi);

    fe.close();


    ifstream fe2("vertex2.txt");
    char cadena2[128];
    // Leeremos mediante getline, si lo hiciéramos
    // mediante el operador >> sólo leeríamos
    // parte de la cadena:
    fe2.getline(cadena2, 128);


    int n_ver2 = atoi(cadena2);

    for (int aux = 0; aux < n_ver2; aux++) {
        char aux_x[128], aux_y[128];
        fe2.getline(aux_x, 128);
        v2_x.push_back(atoi(aux_x));
        fe2.getline(aux_y, 128);
        v2_y.push_back(atoi(aux_y));


    }

fe.getline(auxi, 128);
        
    RGB2[0]=atoi(auxi);
fe.getline(auxi, 128);
        
    RGB2[1]=atoi(auxi);
fe.getline(auxi, 128);
        
    RGB2[2]=atoi(auxi);


    fe2.close();

    for (int aux = 0; aux <= n_ver1; aux++) {
        cout << v_x[aux] << " " << v_y[aux] << endl;
    }

    cout << "kkk " << num1 << endl;

    //Setup four points
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkPoints> points2 = vtkSmartPointer<vtkPoints>::New();
    for (int aux = 0; aux < n_ver1; aux++) {
        points->InsertNextPoint((v_x[aux] + 300) / 3, (v_y[aux] + 600) / 3, 0.0);
        cout << "hola0" <<" "<<(v_x[aux] + 300) / 3<<" "<<(v_y[aux] + 600)/3<<endl;
    }

    for (int aux = 0; aux < n_ver2; aux++) {
        if ((aux + 1) == num3) {
            cout << "hola1" <<" "<<(v_x[num2 - 1] + 300) / 3<<" "<<(v_y[num2 - 1] + 600)/3<<endl;
            points2->InsertNextPoint((v_x[num2 - 1] + 300) / 3, (v_y[num2 - 1] + 600) / 3, 0.0);
        } else if ((aux + 1) == num4) {
           // cout << "hola2" << endl;
             points2->InsertNextPoint((v_x[num1 - 1] + 300) / 3, (v_y[num1 - 1] + 600) / 3, 0.0);
             cout << "hola2" <<" "<<(v_x[num1 - 1] + 300) / 3<<" "<<(v_y[num1 - 1] + 600)/ 3<<endl;
        } else {
           // cout << "hola3" <<" "<<v_x[num1 - 1] + 300) / 3<<" "<<(v_y[num1 - 1] + 600)/ 3<<endl;
            int difx = v2_x[aux] - v2_x[num3 - 1];
            int dify = v2_y[aux] - v2_y[num3 - 1];
            //cout << v_x[num2 - 1] + difx << " " << v_y[num2 - 1] + dify << "||||" << difx << "|||| " << v2_x[aux] << " " << v2_x[num3 - 1] << endl;
            //cout << dify << "||| " << v2_y[aux] << " " << v2_y[num3 - 1] << " " << v_x[num2 - 1] << " " << v_y[num2 - 1] << endl;
            points2->InsertNextPoint(((v_x[num2 - 1] + difx) + 300) / 3, ((v_y[num2 - 1] + dify) + 600) / 3, 0.0);
             cout << "hola3" <<" "<<((v_x[num2 - 1] + difx) + 300) / 3<<" "<<((v_y[num2 - 1] + dify) + 600) / 3<<endl;
        }
    }


    //Create the polygon
    vtkSmartPointer<vtkPolygon> polygon = vtkSmartPointer<vtkPolygon>::New();
    polygon->GetPointIds()->SetNumberOfIds(n_ver1); //make a quad

    for (int cont = 0; cont < (n_ver1); cont++) {

        polygon->GetPointIds()->SetId(cont, cont);
    }



    vtkSmartPointer<vtkCellArray> polygons = vtkSmartPointer<vtkCellArray>::New();
    polygons->InsertNextCell(polygon);

    //Create a PolyData
    vtkSmartPointer<vtkPolyData> polygonPolyData = vtkSmartPointer<vtkPolyData>::New();
    polygonPolyData->SetPoints(points);
    polygonPolyData->SetPolys(polygons);


    vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
    /*transform->RotateWXYZ(45,1,1,0);

    vtkSmartPointer<vtkTransformPolyDataFilter>  transformFilter= vtkSmartPointer<vtkTransformPolyDataFilter> ::New();
    transformFilter->SetTransform(transform);
    transformFilter->SetInput(polygonPolyData);
    transformFilter->Update();
     */
    cout << "Aci estem" << endl;
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    // vtkSmartPointer<vtkActor2D> actor = vtkSmartPointer<vtkActor2D>::New();
    //double color[3] = {RGB1[0],RGB1[1], RGB1[2]};
	double color[3] = {0,0,0};
    /*
      vtkSmartPointer<vtkPolyDataMapper2D> mapper = vtkSmartPointer<vtkPolyDataMapper2D>::New();
      mapper->SetInput( polygonPolyData );
      //mapper->SetInput(transformFilter->GetOutput());
      mapper->ScalarVisibilityOn();
      actor->SetMapper( mapper );
      actor->GetProperty()->SetColor( color );
     */

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInput(polygonPolyData);
    //mapper->SetInput(transformFilter->GetOutput());
    mapper->ScalarVisibilityOn();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(color);
    actor->RotateZ(180);


//Create the polygon 2
    vtkSmartPointer<vtkPolygon> polygon2 = vtkSmartPointer<vtkPolygon>::New();
    polygon2->GetPointIds()->SetNumberOfIds(n_ver2); //make a quad

    for (int cont = 0; cont < (n_ver2); cont++) {

        polygon2->GetPointIds()->SetId(cont, cont);
    }



    vtkSmartPointer<vtkCellArray> polygons2 = vtkSmartPointer<vtkCellArray>::New();
    polygons2->InsertNextCell(polygon2);

    //Create a PolyData
    vtkSmartPointer<vtkPolyData> polygonPolyData2 = vtkSmartPointer<vtkPolyData>::New();
    polygonPolyData2->SetPoints(points2);
    polygonPolyData2->SetPolys(polygons2);


    cout << "Aci estem 2" << endl;
    vtkSmartPointer<vtkActor> actor2 = vtkSmartPointer<vtkActor>::New();
    // vtkSmartPointer<vtkActor2D> actor = vtkSmartPointer<vtkActor2D>::New();
	double color2[3] = {0,0,0};    
//double color2[3] = {RGB2[0],RGB2[1], RGB2[2]};
    /*
      vtkSmartPointer<vtkPolyDataMapper2D> mapper = vtkSmartPointer<vtkPolyDataMapper2D>::New();
      mapper->SetInput( polygonPolyData );
      //mapper->SetInput(transformFilter->GetOutput());
      mapper->ScalarVisibilityOn();
      actor->SetMapper( mapper );
      actor->GetProperty()->SetColor( color );
     */

    vtkSmartPointer<vtkPolyDataMapper> mapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper2->SetInput(polygonPolyData2);
    //mapper->SetInput(transformFilter->GetOutput());
    mapper2->ScalarVisibilityOn();
    actor2->SetMapper(mapper2);
    actor2->GetProperty()->SetColor(color2);
    actor2->RotateZ(180);



    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->AddActor(actor2);

    // Renderer and RenderWindow
    renderer->SetBackground(1, 1, 1);
    //renderer->ResetCamera();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

    renderWindow->SetSize(400, 400);
    renderWindow->AddRenderer(renderer);
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderWindow->Render();
    //renderWindow->Finalize();

    //renderWindow->Start();
    //  renderWindowInteractor->EnableRenderOff();

    //renderWindowInteractor->Stop();


    vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter =
            vtkSmartPointer<vtkWindowToImageFilter>::New();
    windowToImageFilter->SetInput(renderWindow);
    windowToImageFilter->Update();

    vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
    writer->SetFileName("resultat.png");
    writer->SetInput(windowToImageFilter->GetOutput());
    writer->Write();



    //renderWindowInteractor->Start();
    //renderWindowInteractor->SetTimerDuration(0);

    //renderWindowInteractor->TerminateApp();



}


