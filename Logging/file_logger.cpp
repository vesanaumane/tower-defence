#include "file_logger.hpp"

#include <string>
#include <sys/stat.h>
#include <stdexcept>
#include <fstream>
#include <filesystem>

using namespace Logging;

FileLogger::FileLogger( LogLevel maximum_log_level, std::string file_path )
    : LoggerBase( maximum_log_level )
{
    // Create the directories for the file if those do not exist yet.
    std::filesystem::path path( file_path );
    if( path.has_parent_path() )
    {
        std::filesystem::create_directories( path.parent_path() );
    }

    // Open the file in append mode, this will create the file if it does not exist.
    m_file.open( file_path, std::ios::app );
    if( !m_file.is_open() )
    {
        throw std::runtime_error(
            "Failed to open log file: " + file_path
        );
    }

    // Log a header to the file to mark the starting time.
    m_file << "**********************************\n"
        << "*             Start              *\n"
        << "*      " << getCurrentTimestamp() << "       *\n"
        << "**********************************\n";
}

void FileLogger::logError( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( LogLevel::Error, message, add_prefix );
}

void FileLogger::logWarning( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( LogLevel::Warning, message, add_prefix );
}

void FileLogger::logInfo( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( LogLevel::Info, message, add_prefix );
}

void FileLogger::logDebug( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( LogLevel::Debug, message, add_prefix );
}

void FileLogger::logVerbose( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( LogLevel::Verbose, message, add_prefix );
}

FileLogger::~FileLogger()
{
    // Close the file stream.
    if( m_file && m_file.is_open() )
        m_file.close();
}

void FileLogger::logMessage( LogLevel level, std::string message, bool add_prefix )
{
    // Check if the message should be logged at all based on the log level settings.
    if( !shouldLog( level ) )
        return;

    // Add prefix if wanted.
    if( add_prefix )
        prefixMessage( level, message );

    // Write the log.
    m_file << message << '\n';
}
