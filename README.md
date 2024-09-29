# ESI SHARE

ESI SHARE es una aplicación diseñada para facilitar a los alumnos de la Escuela Superior de Ingeniería (ESI) el compartir vehículos con otros estudiantes que vayan a realizar trayectos similares. Esto no solo reduce los costos de transporte, sino que también ayuda a disminuir la huella de carbono de los usuarios.

## Descripción General

ESI SHARE permite la **reserva en tiempo real** de plazas en vehículos que transitan por zonas cercanas a la ubicación del usuario. Los estudiantes pueden registrar sus vehículos y los viajes que planean realizar, permitiendo que otros usuarios reserven una plaza si el trayecto pasa por su zona.

### Funcionalidades Principales

- Registro y administración de **usuarios**.
- **Creación de viajes** con destino controlado por un administrador.
- **Edición de vehículos** y viajes registrados por los usuarios.
- **Determinación automática del precio** del viaje basado en la distancia y el número de ocupantes.
- **Perfiles diferenciados** de administrador y usuario normal. Solo los administradores pueden gestionar todas las reservas y vehículos.

## Tecnologías Utilizadas

- **Lenguaje de programación**: C (ISO/IEC 9899:1990).
- **Bibliotecas**: `stdio.h`, `stdlib.h`, `time.h`, entre otras.
- **Entornos de desarrollo**: Code::Blocks en Windows y Visual Studio Code en GNU/Linux (con GCC).

## Instalación

1. Haz un **fork** de este repositorio en tu cuenta de GitHub.
2. Descarga los archivos del repositorio.
3. Ejecuta el archivo `ESI_SHARE.exe` para iniciar la aplicación. No es necesario un proceso de instalación adicional.

> **Nota**: La aplicación es portable y compatible tanto en **Windows** como en **GNU/Linux**.

## Acceso al Sistema

- Los usuarios deben iniciar sesión con sus credenciales.
- Si se olvida el nombre de usuario, puede consultarse en el archivo `usuarios.txt`.
- Dependiendo del tipo de usuario (administrador o usuario normal), se accederá a un menú con opciones específicas.

## Uso del Sistema

Una vez iniciada la sesión, el usuario podrá:

1. **Gestionar su perfil personal**, editando sus datos y vehículos.
2. **Registrar nuevos viajes** o reservar plaza en los viajes de otros usuarios.
3. **Acceder a vehículos disponibles** para editar o eliminarlos (dependiendo de los permisos).
4. **Consultar viajes** y gestionar sus reservas.

> **Importante**: El precio del viaje es calculado automáticamente y no puede ser modificado ni por el usuario ni por el administrador.

## Licencia

ESI SHARE es un proyecto de código cerrado creado para los alumnos de la Escuela Superior de Ingeniería. No se permite su distribución o modificación sin el permiso expreso de los creadores.

---

¡Gracias por usar ESI SHARE!
