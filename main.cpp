#include <iostream>
#include <string>

// Singleton: existe una sola instancia de Configuracion en toda la aplicación.
class Configuracion {
public:
    // C++11 garantiza que la inicialización local estática es segura entre hilos.
    static Configuracion& obtenerInstancia() {
        static Configuracion instancia;
        return instancia;
    }

    Configuracion(const Configuracion&) = delete;
    Configuracion& operator=(const Configuracion&) = delete;
    Configuracion(Configuracion&&) = delete;
    Configuracion& operator=(Configuracion&&) = delete;

    const std::string& obtenerTema() const { return tema_; }
    void establecerTema(const std::string& tema) { tema_ = tema; }

    int obtenerVolumen() const { return volumen_; }
    void establecerVolumen(int volumen) {
        if (volumen < 0) volumen_ = 0;
        else if (volumen > 100) volumen_ = 100;
        else volumen_ = volumen;
    }

    bool obtenerNotificaciones() const { return notificaciones_; }
    void establecerNotificaciones(bool activadas) {
        notificaciones_ = activadas;
    }

    void mostrar() const {
        std::cout << "Tema: " << tema_ << '\n'
                  << "Volumen: " << volumen_ << "%\n"
                  << "Notificaciones: "
                  << (notificaciones_ ? "activadas" : "desactivadas") << "\n";
    }

private:
    Configuracion() = default;

    std::string tema_ = "Claro";
    int volumen_ = 70;
    bool notificaciones_ = true;
};

void configurarPreferencias() {
    Configuracion& config = Configuracion::obtenerInstancia();
    config.establecerTema("Oscuro");
    config.establecerVolumen(85);
    config.establecerNotificaciones(false);
}

void mostrarPreferencias() {
    const Configuracion& config = Configuracion::obtenerInstancia();
    config.mostrar();
}

int main() {
    std::cout << "Preferencias iniciales:\n";
    mostrarPreferencias();

    std::cout << "\nActualizando preferencias...\n";
    configurarPreferencias();

    std::cout << "\nPreferencias desde otra parte de la aplicación:\n";
    mostrarPreferencias();

    Configuracion& primera = Configuracion::obtenerInstancia();
    Configuracion& segunda = Configuracion::obtenerInstancia();
    std::cout << "\n¿Es la misma instancia? "
              << (&primera == &segunda ? "Sí" : "No") << '\n';
    return 0;
}
